// Include the required Arduino libraries:
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include <TheThingsNetwork.h>
#include <CayenneLPP.hpp>

/* The buffer size to initialize the CayenneLPP instance with */
#define BUFFER_SIZE 50

/* The measurement channel from which the measurements were measured
 * Both the data and measurement channel will be bundled and sent over LoraWAN
 * See the README of CayenneLPP
 */
#define MEASUREMENT_CHANNEL 1

#define loraSerial Serial1
#define debugSerial Serial

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan REPLACE_ME

// Set your AppEUI and AppKey
const char *appEui = "0000000000000000";
const char *appKey = "00000000000000000000000000000000";

Adafruit_MPU6050 mpu;

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

CayenneLPP::CayenneLPP<BUFFER_SIZE> encoder;

void setup() {
  loraSerial.begin(57600);
  debugSerial.begin(9600);

 if (!mpu.begin()) {
    debugSerial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
ttn.join(appEui, appKey);
}

void loop() {
  CayenneLPP::Measurement_t measurement;
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Set measurement to gyro with measured gyro */
  measurement = CayenneLPP::SetGyro(g.x, g.y, g.z);
  
  /* Place the gyro measurement in the encoder buffer */
  encoder.setMeasurement(MEASUREMENT_CHANNEL, &measurement);

  /* Set measurement to accelero with measured accelero */
  measurement = CayenneLPP::SetAcceleration(a.x, a.y, a.z);

  /* Place the accelero measurement in the encoder buffer */
  encoder.setMeasurement(MEASUREMENT_CHANNEL, &measurement);

  /* Set measurement to temperature with measured temperature */
  measurement = CayenneLPP::SetTemperature(temp.temperature);

  /* Get the current cursor pos, to know how much bytes to transmit */
  const uint8_t amount_of_bytes = encoder.setMeasurement(MEASUREMENT_CHANNEL, &measurement);
  /* Get the encoder buffer */
  const uint8_t* data = encoder.getBuffer();
  /* Send the bytes to TTN dash */
  ttn.sendBytes(data, amount_of_bytes);
  /* Reset the encoder */
  encoder.reset();
  // Wait 1 second:
  delay(1000);
}
// Include the required Arduino libraries:
#include "OneWire.h"
#include "DallasTemperature.h"

#include <TheThingsNetwork.h>
#include <CayenneLPP.hpp>

/* The buffer size to initialize the CayenneLPP instance with */
/* For this example a minimum buffer size of 3 is needed, 10 is therefore plenty */
#define BUFFER_SIZE 10

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

// Define to which pin of the Arduino the 1-Wire bus is connected:
#define ONE_WIRE_BUS 2

// Create a new instance of the oneWire class to communicate with any OneWire device:
OneWire oneWire(ONE_WIRE_BUS);

// Pass the oneWire reference to DallasTemperature library:
DallasTemperature sensors(&oneWire);

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

CayenneLPP::CayenneLPP<BUFFER_SIZE> encoder;

void setup() {
  loraSerial.begin(57600);
  debugSerial.begin(9600);

  // Start up the library:
  sensors.begin();
  ttn.join(appEui, appKey);
}

void loop() {
  CayenneLPP::Measurement_t measurement;
  // Send the command for all devices on the bus to perform a temperature conversion:
  sensors.requestTemperatures();

  // Fetch the temperature in degrees Celsius for device index:
  float tempC = sensors.getTempCByIndex(0); // the index 0 refers to the first device

  /* Set measurement to temperature with measured temperature */
  measurement = CayenneLPP::SetTemperature(tempc);

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
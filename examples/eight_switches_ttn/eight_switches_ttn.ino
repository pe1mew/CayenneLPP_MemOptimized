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

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

/* Input pins */
#define NUM_PINS 8
const uint8_t pins[NUM_PINS] = {13, 12, 11, 10, 9, 8, 7, 6};

CayenneLPP::CayenneLPP<BUFFER_SIZE> encoder;

void setup()
{
    loraSerial.begin(57600);
    debugSerial.begin(9600);

    /* Set the pins to input mode */
    for (uint8_t i = 0; i < NUM_PINS; i++)
    {
        pinMode(pins[i], INPUT);
    }

    // Wait a maximum of 10s for Serial Monitor
    while (!debugSerial && millis() < 10000)
        ;

    ttn.join(appEui, appKey);
}

void loop()
{
    CayenneLPP::Measurement_t measurement;
    /* Clear the measurement beforehand! */
    measurement = CayenneLPP::ResetMeasurement();
    /* We don't want to transmit until one pin is high! */
    bool transmit = false;
    for (uint8_t i = 0; i < NUM_PINS; i++)
    {
        /* Read the pin level */
        const uint8_t bit_to_set = digitalRead(pins[i]);
        /* Save the measurement in the measurement struct */
        measurement = CayenneLPP::SetRawBit(bit_to_set, measurement);
        if (bit_to_set)
        {
            /* Button is pushed! Transmit the results after this loop */
            transmit = true;
        }
    }
    if (transmit)
    {
        /* Get the current cursor pos, to know how much bytes to transmit */
        const uint8_t amount_of_bytes = encoder.setMeasurement(MEASUREMENT_CHANNEL, measurement);
        /* Get the encoder buffer */
        const uint8_t* data = encoder.getBuffer();
        /* Send the bytes to TTN dash */
        ttn.sendBytes(data, amount_of_bytes);
        /* Reset the encoder */
        encoder.reset();
    }
    delay(100);
}
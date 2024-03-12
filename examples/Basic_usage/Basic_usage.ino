#include <CayenneLPP.hpp>

/* The buffer size to initialize the CayenneLPP instance with */
#define BUFFER_SIZE 100

/* The measurement channel from which the measurements were measured
 * Both the data and measurement channel will be bundled and sent over LoraWAN
 * See the README of CayenneLPP
 */
#define MEASUREMENT_CHANNEL 1

void setup() {
/* Nothing here :) */
}

void loop() {
/* Statically Initialize the CayenneLPP encoder with 100 bytes buffer */
CayenneLPP::CayenneLPP<BUFFER_SIZE> CayenneEncoder;
CayenneLPP::Measurement_t GPSMeasurement = CayenneLPP::SetGPS(10.0, 50.0, 20.0);
CayenneEncoder.setMeasurement(MEASUREMENT_CHANNEL, GPSMeasurement);
}

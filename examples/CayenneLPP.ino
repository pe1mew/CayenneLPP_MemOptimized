#include <CayenneLPP.hpp>

#define BUFFER_SIZE 100

#define MEASUREMENT_CHANNEL 1

void setup() {
CayenneLPP::CayenneLPP<BUFFER_SIZE> CayenneEncoder;
CayenneLPP::Measurement_t GPSMeasurement
}

void loop() {
GPSMeasurement = CayenneLPP::SetGPS(10.0, 50.0, 20.0);
CayenneEncoder.setMeasurement(MEASUREMENT_CHANNEL, GPSMeasurement);
}
#include "gmock/gmock.h"
#include "CayenneLPP.hpp"


/**
* \brief These test functions are "Fuzz test", which means you can change the variable 'testval' to your desired value, for specific tests.
*        In the funtions we test for 2 different values, 1 where we expect no complaints and 1 faulty value.
*/
TEST(DigitalOutputtest, Valueinput) {
    uint8_t testval = 1;
    CayenneLPP::Measurement_t result = CayenneLPP::SetDigitalOutput(testval);
    EXPECT_EQ(result.val.DigitalGPIO, testval);
    EXPECT_EQ(result.val.RawBytes[0], testval);
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_DIGITAL_OUTPUT);
    testval = 2;
    CayenneLPP::SetDigitalOutput(testval);
    EXPECT_EQ(result.val.DigitalGPIO, testval);
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_DIGITAL_OUTPUT);
}

TEST(DigitalInputtest, Valueinput) {
    uint8_t testval = 0;
    CayenneLPP::Measurement_t result = CayenneLPP::SetDigitalInput(testval);
    EXPECT_EQ(result.val.DigitalGPIO, testval);
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_DIGITAL_INPUT);
    testval = 1;
    result = CayenneLPP::SetDigitalInput(testval);
    EXPECT_EQ(result.val.DigitalGPIO, testval);
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_DIGITAL_INPUT);
}

TEST(SetPresencetest, Valueinput) {
    uint8_t testval = 102;
    CayenneLPP::Measurement_t result = CayenneLPP::SetPresence(testval);
    EXPECT_EQ(result.val.Prescence, testval);
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_PRESENCE);
    testval = 1;
    result = CayenneLPP::SetPresence(testval);
    EXPECT_EQ(result.val.Presence, testval);
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_PRESENCE);
}

TEST(SetLuminositytest, Valueinput) {
    uint16_t testval = 101;
    CayenneLPP::Measurement_t result = CayenneLPP::SetLuminosity(testval);
    EXPECT_EQ(result.val.Luminosity, testval);
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_LUMINOSITY);
    testval = 1;
    result = CayenneLPP::SetLuminosity(testval);
    EXPECT_EQ(result.val.Luminosity, testval);
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_LUMINOSITY);
}

TEST(SetAnalogoutputtest, Valueinput) {
    uint16_t testval = 3;
    CayenneLPP::Measurement_t result = CayenneLPP::SetAnalogOutput(testval);
    EXPECT_EQ(result.val.AnalogGPIO, testval);
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_ANALOG_OUTPUT);
    testval = 1;
    result = CayenneLPP::SetAnalogOutput(testval);
    EXPECT_EQ(result.val.AnalogGPIO, testval);
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_ANALOG_OUTPUT);
}

TEST(SetAnaloginputtest, Valueinput) {
    uint16_t testval = 2;
    CayenneLPP::Measurement_t result = CayenneLPP::SetAnalogInput(testval);
    EXPECT_EQ(result.val.AnalogGPIO, testval);
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_ANALOG_INPUT);
    testval = 1;
    result = CayenneLPP::SetAnalogInput(testval);
    EXPECT_EQ(result.val.AnalogGPIO, testval);
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_ANALOG_INPUT);
}

TEST(SetTemperaturetest, Valueinput) {
    uint16_t testval = 103;
    CayenneLPP::Measurement_t result = CayenneLPP::SetTemperature(testval);
    EXPECT_EQ(result.val.Temperature, testval);
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_TEMPERATURE);
    testval = 1;
    result = CayenneLPP::SetTemperature(testval);
    EXPECT_EQ(result.val.Temperature, testval);
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_TEMPERATURE);
 }

 TEST(SetRelativeHumiditytest, Valueinput) {
    uint16_t testval = 104;
    CayenneLPP::Measurement_t result = CayenneLPP::SetRelativeHumidity(testval);
    EXPECT_EQ(result.val.RelativeHumidity, testval);
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_RELATIVE_HUMIDITY);
    testval = 1;
    result = CayenneLPP::SetRelativeHumidity(testval);
    EXPECT_EQ(result.val.RelativeHumidity, testval);
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_RELATIVE_HUMIDITY);
 }

 TEST(SetBarometricPressuretest, Valueinput) {
    uint16_t testval = 115;
    CayenneLPP::Measurement_t result = CayenneLPP::SetBarometricPressure(testval);
    EXPECT_EQ(result.val.BarometricPressure, testval);
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_BAROMETRIC_PRESSURE);
    testval = 1;
    result = CayenneLPP::SetBarometricPressure(testval);
    EXPECT_EQ(result.val.BarometricPressure, testval);
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_BAROMETRIC_PRESSURE);
 }

 TEST(SeteAccelerationtest, Valueinput) {
    CayenneLPP::AcceleroVal_t testval = {.x = 10.2, .y = 5.7, .z = 10.4};
    CayenneLPP::Measurement_t result = CayenneLPP::SetAcceleration(testval);
    EXPECT_EQ(result.val.Acceleration.x, (testval.x*1000));
    EXPECT_EQ(result.val.Acceleration.y, (testval.y*1000));
    EXPECT_EQ(result.val.Acceleration.z, (testval.z*1000));
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_ACCELERATION);
 }

 TEST(SetGPStest, Valueinput) {
    CayenneLPP::GPSCoord_t testval = {.x = 52.4, .y = 2.1, .z = 86.7};
    CayenneLPP::Measurement_t result = CayenneLPP::SetGPS(testval);
    EXPECT_EQ(result.val.GPS.x, (testval.x*10000));
    EXPECT_EQ(result.val.GPS.y, (testval.y*10000));
    EXPECT_EQ(result.val.GPS.z, (testval.z*10000));
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_GPS);
 }

 TEST(SetGyrotest, Valueinput) {
    CayenneLPP::Gyroval_t testval = {.x = 4.6, .y = 2.2, .z = 8.6};
    CayenneLPP::Measurement_t result = CayenneLPP::SetGyro(testval);
    EXPECT_EQ(result.val.Gyro.x, (testval.x*100));
    EXPECT_EQ(result.val.Gyro.y, (testval.y*100));
    EXPECT_EQ(result.val.Gyro.z, (testval.z*100));
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_GYRO);
 }

 TEST(SetRawBittest, Valueinput) {
    uint8_t testval = 116;
    CayenneLPP::Measurement_t result = CayenneLPP::SetGyro(testval);
    EXPECT_EQ(result.val.Gyro, testval);
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_GYRO);
    testval = 1;
    result = CayenneLPP::SetGyro(testval);
    EXPECT_EQ(result.val.Gyro, testval);
    EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_GYRO);
 }


int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);

    if (RUN_ALL_TESTS()) {}
    return 0;
}

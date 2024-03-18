#include "gmock/gmock.h"
#include "CayenneLPP.hpp"

#define CREATE_RANDOM_LUM_VAL static_cast<float>((static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100))))
#define CREATE_RANDOM_ANALOG_VOLT_VAL (static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/5)))

TEST(DigitalOutputtest, Functioning)
{
   uint8_t testval = 1;
   CayenneLPP::Measurement_t result = CayenneLPP::SetDigitalOutput(testval);
   EXPECT_EQ(result.val.DigitalGPIO, (testval > 0));
   EXPECT_EQ(result.val.RawBytes[0], (testval > 0));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_DIGITAL_OUTPUT);
   testval = 0;
   result = CayenneLPP::SetDigitalOutput(testval);
   EXPECT_EQ(result.val.DigitalGPIO, (testval > 0));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_DIGITAL_OUTPUT);
}

TEST(DigitalOutputtest, InvalidParameter)
{
   uint8_t testval = 100;
   CayenneLPP::Measurement_t result = CayenneLPP::SetDigitalOutput(testval);
   EXPECT_EQ(result.val.DigitalGPIO, (testval > 0));
   EXPECT_EQ(result.val.RawBytes[0], (testval > 0));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_DIGITAL_OUTPUT);
   testval = (rand() & 0xFF);
   result = CayenneLPP::SetDigitalOutput(testval);
   EXPECT_EQ(result.val.DigitalGPIO, (testval > 0));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_DIGITAL_OUTPUT);  
}

TEST(DigitalInputtest, Functioning)
{
   uint8_t testval = 0;
   CayenneLPP::Measurement_t result = CayenneLPP::SetDigitalInput(testval);
   EXPECT_EQ(result.val.DigitalGPIO, (testval > 0));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_DIGITAL_INPUT);
   testval = 1;
   result = CayenneLPP::SetDigitalInput(testval);
   EXPECT_EQ(result.val.DigitalGPIO, (testval > 0));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_DIGITAL_INPUT);
}

TEST(DigitalInputtest, InvalidParameter)
{
   uint8_t testval = 100;
   CayenneLPP::Measurement_t result = CayenneLPP::SetDigitalInput(testval);
   EXPECT_EQ(result.val.DigitalGPIO, (testval > 0));
   EXPECT_EQ(result.val.RawBytes[0], (testval > 0));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_DIGITAL_INPUT);
   testval = (rand() & 0xFF);
   result = CayenneLPP::SetDigitalInput(testval);
   EXPECT_EQ(result.val.DigitalGPIO, (testval > 0));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_DIGITAL_INPUT);  
}

TEST(SetPresencetest, Functioning)
{
   uint8_t testval = 102;
   CayenneLPP::Measurement_t result = CayenneLPP::SetPresence(testval);
   EXPECT_EQ(result.val.Presence, (testval > 0) );
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_PRESENCE);
   testval = 1;
   result = CayenneLPP::SetPresence(testval);
   EXPECT_EQ(result.val.Presence, (testval > 0));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_PRESENCE);
}

TEST(SetPresencetest, InvalidParameter)
{
   uint8_t testval = (rand() & 0xFF);
   CayenneLPP::Measurement_t result = CayenneLPP::SetPresence(testval);
   EXPECT_EQ(result.val.Presence, (testval > 0));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_PRESENCE);
   testval = 1;
   result = CayenneLPP::SetPresence(testval);
   EXPECT_EQ(result.val.Presence, (testval > 0));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_PRESENCE);
}


TEST(SetLuminositytest, Functioning)
{
   float testval = 10.1;
   CayenneLPP::Measurement_t result = CayenneLPP::SetLuminosity(testval);
   EXPECT_EQ(result.val.Luminosity, uint16_t(testval * 100));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_LUMINOSITY);
   testval = 1;
   result = CayenneLPP::SetLuminosity(testval);
   EXPECT_EQ(result.val.Luminosity, uint16_t(testval * 100));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_LUMINOSITY);
}

TEST(SetLuminositytest, InvalidParameter)
{
   float testval = CREATE_RANDOM_LUM_VAL;
   CayenneLPP::Measurement_t result = CayenneLPP::SetLuminosity(testval);
   EXPECT_EQ(result.val.Luminosity, uint16_t(testval * 100));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_LUMINOSITY);
   testval = CREATE_RANDOM_LUM_VAL;
   result = CayenneLPP::SetLuminosity(testval);
   EXPECT_EQ(result.val.Luminosity, uint16_t(testval * 100));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_LUMINOSITY);
}


TEST(SetAnalogoutputtest, Functioning)
{
   float testval = 0.2;
   CayenneLPP::Measurement_t result = CayenneLPP::SetAnalogOutput(testval);
   EXPECT_EQ(result.val.AnalogGPIO, uint16_t(testval * 100));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_ANALOG_OUTPUT);
   testval = 5.1;
   result = CayenneLPP::SetAnalogOutput(testval);
   EXPECT_EQ(result.val.AnalogGPIO, uint16_t(testval * 100));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_ANALOG_OUTPUT);
}

TEST(SetAnalogoutputtest, InvalidParameter)
{
   float testval = 0.2;
   CayenneLPP::Measurement_t result = CayenneLPP::SetAnalogOutput(testval);
   EXPECT_EQ(result.val.AnalogGPIO, uint16_t(testval * 100));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_ANALOG_OUTPUT);
   testval = 5.1;
   result = CayenneLPP::SetAnalogOutput(testval);
   EXPECT_EQ(result.val.AnalogGPIO, uint16_t(testval * 100));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_ANALOG_OUTPUT);
}

TEST(SetAnaloginputtest, Functioning)
{
   float testval = 0.2;
   CayenneLPP::Measurement_t result = CayenneLPP::SetAnalogInput(testval);
   EXPECT_EQ(result.val.AnalogGPIO, uint16_t(testval * 100));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_ANALOG_INPUT);
   testval = 5.1;
   result = CayenneLPP::SetAnalogInput(testval);
   EXPECT_EQ(result.val.AnalogGPIO, uint16_t(testval * 100));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_ANALOG_INPUT);
}

TEST(SetTemperaturetest, Functioning)
{
   float testval = 10.3;
   CayenneLPP::Measurement_t result = CayenneLPP::SetTemperature(testval);
   EXPECT_EQ(result.val.Temperature, (testval * 10));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_TEMPERATURE);
   testval = 20.1;
   result = CayenneLPP::SetTemperature(testval);
   EXPECT_EQ(result.val.Temperature, (testval * 10));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_TEMPERATURE);
}

TEST(SetRelativeHumiditytest, Functioning)
{
   float testval = 1000.50;
   CayenneLPP::Measurement_t result = CayenneLPP::SetRelativeHumidity(testval);
   EXPECT_EQ(result.val.RelativeHumidity, uint16_t(testval * 2));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_RELATIVE_HUMIDITY);
   testval = 1100.2;
   result = CayenneLPP::SetRelativeHumidity(testval);
   EXPECT_EQ(result.val.RelativeHumidity, uint16_t(testval * 2));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_RELATIVE_HUMIDITY);
}

TEST(SetBarometricPressuretest, Functioning)
{
   float testval = 13.45;
   CayenneLPP::Measurement_t result = CayenneLPP::SetBarometricPressure(testval);
   EXPECT_EQ(result.val.BarometricPressure, uint16_t(testval * 10));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_BAROMETRIC_PRESSURE);
   testval = 10.58;
   result = CayenneLPP::SetBarometricPressure(testval);
   EXPECT_EQ(result.val.BarometricPressure, uint16_t(testval * 10));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_BAROMETRIC_PRESSURE);
}

TEST(SeteAccelerationtest, Functioning)
{
   float x, y, z;
   x = 10.2;
   y = 5.7;
   z = 10.4;
   CayenneLPP::Measurement_t result = CayenneLPP::SetAcceleration(x, y, z);
   EXPECT_EQ(result.val.Acceleration.x, (x * 1000));
   EXPECT_EQ(result.val.Acceleration.y, (y * 1000));
   EXPECT_EQ(result.val.Acceleration.z, (z * 1000));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_ACCELERATION);
}

TEST(SetGPStest, Functioning)
{
   float latitude, longitude, altitude;
   latitude = 52.4;
   longitude = 2.1;
   altitude = 10.7;
   CayenneLPP::Measurement_t result = CayenneLPP::SetGPS(latitude, longitude, altitude);
   CayenneLPP::GPSCoord_t endresult = {uint32_t(latitude * 10000), uint32_t(longitude * 10000), uint32_t(altitude * 100)};
   EXPECT_EQ(result.val.GPS.latitude, endresult.latitude);
   EXPECT_EQ(result.val.GPS.longitude, endresult.longitude);
   EXPECT_EQ(result.val.GPS.altitude, endresult.altitude);
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_GPS);
}

TEST(SetGyrotest, Functioning)
{
   float x, y, z;
   x = 4.6;
   y = 2.2;
   z = 8.6;
   CayenneLPP::Measurement_t result = CayenneLPP::SetGyro(x, y, z);
   EXPECT_EQ(result.val.Gyro.x, uint16_t(x * 100));
   EXPECT_EQ(result.val.Gyro.y, uint16_t(y * 100));
   EXPECT_EQ(result.val.Gyro.z, uint16_t(z * 100));
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_GYRO);
}

TEST(SetRawBittest, Functioning)
{
   CayenneLPP::Measurement_t result;
   uint8_t res = 0;
   uint8_t bitval = 0;
   CayenneLPP::CayenneMeasurementType_t expected_type;
   for (uint8_t i = 0; i < 8; i++)
   {
      bitval = rand() > 1 ? 1 : 0;
      CayenneLPP::SetRawBit(bitval, &result);
      res |= (bitval << i);
      expected_type = static_cast<CayenneLPP::CayenneMeasurementType_t>(CayenneLPP::MEASUREMENT_TYPE_RAWBIT_1 + i);
      EXPECT_EQ(result.val.RawBit, res);
      EXPECT_EQ(result.type, expected_type);
   }
}

TEST(SetRawBytetest, Functioning)
{
   uint8_t testval = 5;
   CayenneLPP::Measurement_t result = CayenneLPP::SetRawByte(testval);
   EXPECT_EQ(result.val.RawByte, testval);
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_RAWBYTE);
   testval = 1;
   result = CayenneLPP::SetRawByte(testval);
   EXPECT_EQ(result.val.RawByte, testval);
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_RAWBYTE);
}

TEST(SetWord16test, Functioning)
{
   uint16_t testval = 6;
   CayenneLPP::Measurement_t result = CayenneLPP::SetWord16(testval);
   EXPECT_EQ(result.val.Word16, testval);
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_RAWWORD16);
   testval = 1;
   result = CayenneLPP::SetWord16(testval);
   EXPECT_EQ(result.val.Word16, testval);
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_RAWWORD16);
}

TEST(SetWord32test, Functioning)
{
   CayenneLPP::Word32Val_t testval = 7;
   CayenneLPP::Measurement_t result = CayenneLPP::SetWord32(testval);
   EXPECT_EQ(result.val.Word32, testval);
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_RAWWORD32);
   testval = 1;
   result = CayenneLPP::SetWord32(testval);
   EXPECT_EQ(result.val.Word32, testval);
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_RAWWORD32);
}

TEST(SetFloat32test, Functioning)
{
   CayenneLPP::Float32Val_t testval = 7;
   CayenneLPP::Measurement_t result = CayenneLPP::SetFloat32(testval);
   EXPECT_EQ(result.val.Float32, testval);
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_RAWFLOAT32);
   testval = 1;
   result = CayenneLPP::SetFloat32(testval);
   EXPECT_EQ(result.val.Float32, testval);
   EXPECT_EQ(result.type, CayenneLPP::MEASUREMENT_TYPE_RAWFLOAT32);
}

int main(int argc, char **argv)
{
   ::testing::InitGoogleMock(&argc, argv);

   if (RUN_ALL_TESTS())
   {
   }
   return 0;
}

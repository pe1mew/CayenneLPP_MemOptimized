#ifndef CayenneTypes_HPP
#define CayenneTypes_HPP
namespace CayenneLPP
{

#define CAYENNE_MAX_UNION_SIZE (3 * (sizeof(uint16_t)))

    typedef uint8_t RawByteVal_t;

    typedef uint8_t RawBitVal_t;

    typedef uint16_t Word16Val_t;

    typedef uint32_t Word32Val_t;

    typedef float Float32Val_t;

    typedef uint8_t DigitalGPIOVal_t;

    typedef uint8_t PresenceVal_t;

    typedef uint16_t LuminosityVal_t;

    typedef uint16_t AnalogGPIOVal_t;

    typedef uint16_t TemperatureVal_t;

    typedef uint16_t RelativeHumidity_t;

    typedef uint16_t BarometricPressure_t;

    typedef struct
    {
        uint16_t x;
        uint16_t y;
        uint16_t z;
    } CayenneGyroVal_t;

    typedef struct
    {
        uint16_t x;
        uint16_t y;
        uint16_t z;
    } CayenneAcceleroVal_t;

#pragma pack(push, 1)
    typedef struct
    {
        uint32_t latitude : 24;
        uint32_t longitude : 24;
        uint32_t altitude : 24;
    } CayenneGPSCoord_t;
#pragma pack(pop)

    typedef union
    {
        RawBitVal_t RawBit;
        RawByteVal_t RawByte;
        DigitalGPIOVal_t DigitalGPIO;
        PresenceVal_t Presence;
        Word16Val_t Word16;
        LuminosityVal_t Luminosity;
        AnalogGPIOVal_t AnalogGPIO;
        TemperatureVal_t Temperature;
        RelativeHumidity_t RelativeHumidity;
        BarometricPressure_t BarometricPressure;
        Word32Val_t Word32;
        Float32Val_t Float32;
        CayenneGPSCoord_t GPS;
        CayenneAcceleroVal_t Acceleration;
        CayenneGyroVal_t Gyro;
        uint8_t RawBytes[CAYENNE_MAX_UNION_SIZE];
    } CayenneMeasurementData_t;

    typedef enum
    {
        MEASUREMENT_TYPE_DIGITAL_OUTPUT = 1,
        MEASUREMENT_TYPE_DIGITAL_INPUT = 0,
        MEASUREMENT_TYPE_RAWBIT_1 = 116,
        MEASUREMENT_TYPE_RAWBIT_2 = 117,
        MEASUREMENT_TYPE_RAWBIT_3 = 118,
        MEASUREMENT_TYPE_RAWBIT_4 = 119,
        MEASUREMENT_TYPE_RAWBIT_5 = 120,
        MEASUREMENT_TYPE_RAWBIT_6 = 121,
        MEASUREMENT_TYPE_RAWBIT_7 = 122,
        MEASUREMENT_TYPE_RAWBIT_8 = 123,
        MEASUREMENT_TYPE_RAWBYTE = 5,
        MEASUREMENT_TYPE_RAWWORD16 = 6,
        MEASUREMENT_TYPE_RAWWORD32 = 7,
        MEASUREMENT_TYPE_RAWFLOAT32 = 8,
        MEASUREMENT_TYPE_PRESENCE = 102,
        MEASUREMENT_TYPE_LUMINOSITY = 101,
        MEASUREMENT_TYPE_ANALOG_OUTPUT = 3,
        MEASUREMENT_TYPE_ANALOG_INPUT = 2,
        MEASUREMENT_TYPE_TEMPERATURE = 103,
        MEASUREMENT_TYPE_RELATIVE_HUMIDITY = 104,
        MEASUREMENT_TYPE_BAROMETRIC_PRESSURE = 115,
        MEASUREMENT_TYPE_ACCELERATION = 113,
        MEASUREMENT_TYPE_GYRO = 134,
        MEASUREMENT_TYPE_GPS = 136,
    } CayenneMeasurementType_t;

    typedef struct
    {
        CayenneMeasurementType_t type;
        CayenneMeasurementData_t val;
    } Measurement_t;

    static inline Measurement_t SetDigitalOutput(const uint8_t digital_output_val)
    {
        return {.type = MEASUREMENT_TYPE_DIGITAL_OUTPUT, {.DigitalGPIO = digital_output_val}};
    }

    static inline Measurement_t SetDigitalInput(const uint8_t digital_input_val)
    {
        return {.type = MEASUREMENT_TYPE_DIGITAL_INPUT, {.DigitalGPIO = digital_input_val}};
    }

    static inline Measurement_t SetPresence(const uint8_t presence_val)
    {
        return {.type = MEASUREMENT_TYPE_PRESENCE, {.Presence = presence_val}};
    }

    static inline Measurement_t SetLuminosity(const uint16_t luminosity_val)
    {
        return {.type = MEASUREMENT_TYPE_LUMINOSITY, {.Luminosity = luminosity_val}};
    }

    static inline Measurement_t SetAnalogOutput(const float analog_output_val)
    {
        return {.type = MEASUREMENT_TYPE_ANALOG_OUTPUT, {.AnalogGPIO = uint16_t((analog_output_val * 100))}};
    }

    static inline Measurement_t SetAnalogInput(const float analog_input_val)
    {
        return {.type = MEASUREMENT_TYPE_ANALOG_INPUT, {.AnalogGPIO = uint16_t((analog_input_val * 100))}};
    }

    static inline Measurement_t SetTemperature(const float temperature_val)
    {
        return {.type = MEASUREMENT_TYPE_TEMPERATURE, {.Temperature = uint16_t(temperature_val * 10)}};
    }

    static inline Measurement_t SetRelativeHumidity(const float humidity_val)
    {
        return {.type = MEASUREMENT_TYPE_RELATIVE_HUMIDITY, {.RelativeHumidity = uint16_t(humidity_val * 2)}};
    }

    static inline Measurement_t SetBarometricPressure(const float barometric_pressure_val)
    {
        return {.type = MEASUREMENT_TYPE_BAROMETRIC_PRESSURE, {.BarometricPressure = uint16_t(barometric_pressure_val * 10)}};
    }

    static inline Measurement_t SetAcceleration(const float x, const float y, const float z)
    {
        const CayenneAcceleroVal_t accelero_val = {.x = uint16_t(x * 1000), .y = uint16_t(y * 1000), .z = uint16_t(z * 1000)};
        return {.type = MEASUREMENT_TYPE_ACCELERATION, {.Acceleration = accelero_val}};
    }

    static inline Measurement_t SetGyro(const float x, const float y, const float z)
    {
        const CayenneGyroVal_t gyro_val = {.x = uint16_t(x * 100), .y = uint16_t(y * 100), .z = uint16_t(z * 100)};
        return {.type = MEASUREMENT_TYPE_GYRO, {.Gyro = gyro_val}};
    }

    static inline Measurement_t SetGPS(const float latitude, const float longitude, const float altitude)
    {
        const CayenneGPSCoord_t gps_val = {.latitude = uint32_t(latitude * 10000), .longitude = uint32_t(longitude * 10000), .altitude = uint32_t(altitude * 100)};
        return {.type = MEASUREMENT_TYPE_GPS, {.GPS = gps_val}};
    }

    static inline Measurement_t SetRawBit(const uint8_t raw_bit_val, Measurement_t &prevMeasurement)
    {
        const uint8_t prevMeasurementWasBit = (prevMeasurement.type >= MEASUREMENT_TYPE_RAWBIT_1 && prevMeasurement.type < MEASUREMENT_TYPE_RAWBIT_8);
        uint8_t bitpos = prevMeasurementWasBit ? prevMeasurement.type - MEASUREMENT_TYPE_RAWBIT_1 : 0;
        if (bitpos)
        {
            prevMeasurement.val.RawBit |= (1 << bitpos);
            bitpos++;
            prevMeasurement.type = static_cast<CayenneMeasurementType_t>(MEASUREMENT_TYPE_RAWBIT_1 + bitpos);
        }
        else
        {
            prevMeasurement.val.RawBit = (1 << bitpos);
            prevMeasurement.type = MEASUREMENT_TYPE_RAWBIT_1;
        }
        return prevMeasurement;
    }

    static inline Measurement_t SetRawByte(const uint8_t raw_byte_val)
    {
        const RawByteVal_t raw_byte = raw_byte_val;
        return {.type = MEASUREMENT_TYPE_RAWBYTE, {.RawByte = raw_byte}};
    }

    static inline Measurement_t SetWord16(const uint16_t word16_val)
    {
        const Word16Val_t word16 = word16_val;
        return {.type = MEASUREMENT_TYPE_RAWWORD16, {.Word16 = word16}};
    }

    static inline Measurement_t SetWord32(const uint32_t word32_val)
    {
        const Word32Val_t word32 = word32_val;
        return {.type = MEASUREMENT_TYPE_RAWWORD32, {.Word32 = word32}};
    }

    static inline Measurement_t SetFloat32(const float float32_val)
    {
        const Float32Val_t float32 = float32_val;
        return {.type = MEASUREMENT_TYPE_RAWFLOAT32, {.Float32 = float32}};
    }
}
#endif
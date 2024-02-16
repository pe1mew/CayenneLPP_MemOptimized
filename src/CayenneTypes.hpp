#ifndef CayenneTypes_HPP
#define CayenneTypes_HPP

#define CAYENNE_MAX_UNION_SIZE (3*(sizeof(uint16_t)))

typedef uint8_t CayenneDigitalGPIOVal_t;

typedef uint8_t CayennePresenceVal_t;

typedef uint16_t CayenneLuminosityVal_t;

typedef uint16_t CayenneAnalogGPIOVal_t;

typedef uint16_t CayenneTemperatureVal_t;

typedef uint16_t CayenneRelativeHumidity_t;

typedef uint16_t CayenneBarometricPressure_t;

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
    uint32_t lat : 24;
    uint32_t longitude : 24;
    uint32_t altitude : 24;
} CayenneGPSCoord_t;
#pragma pack(pop)

typedef union
{
    CayenneDigitalGPIOVal_t DigitalGPIO;
    CayennePresenceVal_t Presence;
    CayenneLuminosityVal_t Luminosity;
    CayenneAnalogGPIOVal_t AnalogGPIO;
    CayenneTemperatureVal_t Temperature;
    CayenneRelativeHumidity_t RelativeHumidity;
    CayenneBarometricPressure_t BarometricPressure;
    CayenneGPSCoord_t GPS;
    CayenneAcceleroVal_t Acceleration;
    CayenneGyroVal_t Gyro;
    const uint8_t RawBytes[CAYENNE_MAX_UNION_SIZE];
} CayenneMeasurementData_t;

typedef enum
{
    MEASUREMENT_TYPE_DIGITAL_OUTPUT = 1,
    MEASUREMENT_TYPE_DIGITAL_INPUT = 0,
    MEASUREMENT_TYPE_PRESENCE = 102,
    MEASUREMENT_TYPE_LUMINOSITY = 101,
    MEASUREMENT_TYPE_ANALOG_OUTPUT = 3,
    MEASUREMENT_TYPE_ANALOG_INPUT = 2,
    MEASUREMENT_TYPE_TEMPERATURE = 103,
    MEASUREMENT_TYPE_RELATIVE_HUMIDITY = 104,
    MEASUREMENT_TYPE_BAROMETRIC_PRESSURE = 115,
    MEASUREMENT_TYPE_ACCELERATION = 113,
    MEASUREMENT_TYPE_GYRO = 134,
    MEASUREMENT_TYPE_GPS = 136
} CayenneMeasurementType_t;

typedef struct
{
    CayenneMeasurementType_t type;
    CayenneMeasurementData_t val;
} CayenneMeasurement_t;

static inline CayenneMeasurement_t CayenneMeasurementSetDigitalOutput(const CayenneDigitalGPIOVal_t digital_output_val) {
    return {.type=MEASUREMENT_TYPE_DIGITAL_OUTPUT, .val=digital_output_val};

}

static inline CayenneMeasurement_t CayenneMeasurementSetDigitalInput(const CayenneDigitalGPIOVal_t digital_input_val) {
    return {.type=MEASUREMENT_TYPE_DIGITAL_INPUT, .val=digital_input_val};
}

// static inline CayenneMeasurement_t CayenneMeasurementSetPresence(const CayennePresenceVal_t presence_val) {
//     return {.type=MEASUREMENT_TYPE_PRESENCE, .val=presence_val};
// }

// static inline CayenneMeasurement_t CayenneMeasurementSetLuminosity(const CayenneLuminosityVal_t luminosity_val) {
//     return {.type=MEASUREMENT_TYPE_LUMINOSITY, .val=luminosity_val};
// }

// static inline CayenneMeasurement_t CayenneMeasurementSetAnalogOutput(const float analog_output_val) {
//     return {.type=MEASUREMENT_TYPE_ANALOG_OUTPUT, .val=(analog_output_val*100)};
// }

// static inline CayenneMeasurement_t CayenneMeasurementSetAnalogInput(const float analog_input_val) {
//     return {.type=MEASUREMENT_TYPE_ANALOG_INPUT, .val=(analog_input_val*100)};
// }

// static inline CayenneMeasurement_t CayenneMeasurementSetRelativeHumidity(const CayenneRelativeHumidity_t humidity_val) {
//     CayenneMeasurement_t measurement;
//     measurement.type = MEASUREMENT_TYPE_RELATIVE_HUMIDITY; // Assuming there's a corresponding enum value for relative humidity
//     measurement.val.RelativeHumidity = humidity_val;
//     return measurement;
// }

// static inline CayenneMeasurement_t CayenneMeasurementSetTemperature(const CayenneTemperatureVal_t temperature_val) {
//     CayenneMeasurementData_t data;
//     data.Temperature = temperature_val;
//     return {.type=MEASUREMENT_TYPE_TEMPERATURE, .val=data};
// }

// static inline CayenneMeasurement_t CayenneMeasurementSetRelativeHumidity(const CayenneRelativeHumidity_t humidity_val) {
//     return {.type=MEASUREMENT_TYPE_RELATIVE_HUMIDITY, .val=humidity_val};
// }

// static inline CayenneMeasurement_t CayenneMeasurementSetBarometricPressure(const CayenneBarometricPressure_t barometric_pressure_val) {
//     return {.type=MEASUREMENT_TYPE_BAROMETRIC_PRESSURE, .val=barometric_pressure_val};
// }

// static inline CayenneMeasurement_t CayenneMeasurementSetAcceleration(const float x, const float y, const float z) {
//     CayenneAcceleroVal_t accelero_val = {.x = (x * 1000), .y = (y * 1000), .z = (z * 1000)};
//     return {.type=MEASUREMENT_TYPE_ACCELERATION, .val.Acceleration=accelero_val};
// }


#endif
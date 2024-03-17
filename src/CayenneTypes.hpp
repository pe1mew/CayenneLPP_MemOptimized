/*
*  Copyright 2024 (C) CayenneLPP library
*
*  Licensed under the GPL License, Version 3.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*  https://fsf.org/
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
* Authors: Adrian Sanchez del C. <asanchezdelc>
*          Jarno           <JarnoW999>
*          Majid           <majidsabbagh>
*          Victor Hogeweij <Hoog-V>
*/
#ifndef CayenneTypes_HPP
#define CayenneTypes_HPP
namespace CayenneLPP
{

/*!
 * \brief The max size of the union
 */
#define CAYENNE_MAX_UNION_SIZE (sizeof(GPSCoord_t))

    /*!
     *  Represents a raw byte value, typically used for byte-oriented data operations.
    */
    typedef uint8_t RawByteVal_t;

    /*!
     * Represents a single bit value, often used in bit manipulation or status indication.
    */ 
    typedef uint8_t RawBitVal_t;

    // Represents a 16-bit word, commonly used for medium-range integer values.
    typedef uint16_t Word16Val_t;

    /***
     * Represents a 32-bit word, used for larger integer values or raw data.
    */
    typedef uint32_t Word32Val_t;

    /*** 
     * Represents a 32-bit floating-point number, used for precise numerical values.
    */
    typedef float Float32Val_t;

    /***
     * Represents a digital GPIO (General Purpose Input/Output) value, for digital pin states.
    */
    typedef uint8_t DigitalGPIOVal_t;

    /***
     * Represents a presence detection value, typically indicating detection (1) or absence (0).
    */
    typedef uint8_t PresenceVal_t;

    /***
     * Represents a luminosity value, used for light intensity measurements.
    */ 
    typedef uint16_t LuminosityVal_t;

    /***
     * Represents an analog GPIO value, for analog pin readings.
    */
    typedef uint16_t AnalogGPIOVal_t;

    /***
     * Represents a temperature measurement, typically in a scaled format for precision.
    */
    typedef uint16_t TemperatureVal_t;

    /***
     * Represents relative humidity as a percentage, in a scaled format for precision.
    */
    typedef uint16_t RelativeHumidity_t;

    /***
     * Represents barometric pressure, typically in a scaled format to represent hPa values.
    */
    typedef uint16_t BarometricPressure_t;

    /*!
     * Represents 3-axis gyroscopic values, for orientation or rotational motion detection.
    */
#pragma pack(push, 1)
    typedef struct
    {
        uint16_t x;
        uint16_t y;
        uint16_t z;
    } GyroVal_t;
#pragma pack(pop)

    /***
     * Represents 3-axis acceleration values, for motion or orientation detection.
    */
#pragma pack(push, 1)
    typedef struct
    {
        uint16_t x;
        uint16_t y;
        uint16_t z;
    } AcceleroVal_t;
#pragma pack(pop)

    /***
     * Represents GPS coordinates (latitude, longitude) and altitude, with compact bit field packing.
    */
#pragma pack(push, 1)
    typedef struct
    {
        uint32_t latitude : 24;  /* Latitude, scaled to store fractional degrees */
        uint32_t longitude : 24; /* Longitude, scaled to store fractional degrees */
        uint32_t altitude : 24;  /* Altitude, scaled to store values with precision */
    } GPSCoord_t;
#pragma pack(pop)

    /***
     * Represents a union of all possible measurement values, allowing for diverse data types.
    */
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
        GPSCoord_t GPS;
        AcceleroVal_t Acceleration;
        GyroVal_t Gyro;
        uint8_t RawBytes[CAYENNE_MAX_UNION_SIZE];
    } MeasurementData_t;

    // Defines the measurement types, corresponding to specific data representations.
    typedef enum
    {
        MEASUREMENT_TYPE_INVALID = 255,
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

    // Represents a general-purpose measurement structure, including type and value.
    typedef struct
    {
        CayenneMeasurementType_t type;
        MeasurementData_t val;
    } Measurement_t;


    /**
     * @brief Clears currently used Measurement struct with invalid data
     * 
     * @return Measurement_t A Measurement_t structure initialized with invalid data
     */
    static inline Measurement_t ResetMeasurement() {
        MeasurementData_t Data = {.RawByte = 0};
        return {MEASUREMENT_TYPE_INVALID, Data};
    }

    /**
     * @brief Sets the digital output value.
     *
     * This function initializes a Measurement_t structure with the given digital output value
     * and sets the measurement type to MEASUREMENT_TYPE_DIGITAL_OUTPUT. It is designed to be
     * used for configuring or controlling digital output pins in hardware abstraction layers.
     *
     * @param digital_output_val The digital output value to set. This value is typically
     *        used to control a digital output, such as setting a pin high (1) or low (0).
     * @return Measurement_t A Measurement_t structure initialized with the digital output value
     *         and the type set to MEASUREMENT_TYPE_DIGITAL_OUTPUT.
     */
    static inline Measurement_t SetDigitalOutput(const uint8_t digital_output_val)
    {
        MeasurementData_t Data = {.DigitalGPIO = digital_output_val};
        return {MEASUREMENT_TYPE_DIGITAL_OUTPUT, Data};
    }

    /**
     * @brief Sets the digital input value.
     *
     * This function initializes a Measurement_t structure with the given digital input value
     * and sets the measurement type to MEASUREMENT_TYPE_DIGITAL_INPUT. It is primarily used
     * for capturing or simulating the state of digital input pins in hardware abstraction layers.
     *
     * @param digital_input_val The digital input value to set. This value is typically
     *        used to represent the state of a digital input, such as reading a pin as high (1) or low (0).
     * @return Measurement_t A Measurement_t structure initialized with the digital input value
     *         and the type set to MEASUREMENT_TYPE_DIGITAL_INPUT.
     */
    static inline Measurement_t SetDigitalInput(const uint8_t digital_input_val)
    {
        MeasurementData_t Data = {.DigitalGPIO = digital_input_val};
        return {MEASUREMENT_TYPE_DIGITAL_INPUT, Data};
    }

    /**
     * @brief Sets the presence value.
     *
     * This function initializes a Measurement_t structure with the given presence value
     * and sets the measurement type to MEASUREMENT_TYPE_PRESENCE. It is designed to be
     * used for representing the presence or absence of an object or entity, typically detected
     * through sensors.
     *
     * @param presence_val The presence value to set. This value is typically
     *        used to indicate the detection of presence (1) or absence (0) of an entity.
     * @return Measurement_t A Measurement_t structure initialized with the presence value
     *         and the type set to MEASUREMENT_TYPE_PRESENCE.
     */
    static inline Measurement_t SetPresence(const uint8_t presence_val)
    {
        MeasurementData_t Data = {.Presence = presence_val};
        return {MEASUREMENT_TYPE_PRESENCE, Data};
    }

    /**
     * @brief Sets the luminosity value.
     *
     * This function initializes a Measurement_t structure with the given luminosity value
     * and sets the measurement type to MEASUREMENT_TYPE_LUMINOSITY. It is primarily used
     * for monitoring or simulating light intensity levels in various applications, ranging from
     * environmental sensing to smart lighting control.
     *
     * @param luminosity_val The luminosity value to set. This value typically represents
     *        the intensity of light measured, using a specific unit such as lux.
     * @return Measurement_t A Measurement_t structure initialized with the luminosity value
     *         and the type set to MEASUREMENT_TYPE_LUMINOSITY.
     */
    static inline Measurement_t SetLuminosity(const uint16_t luminosity_val)
    {
        MeasurementData_t Data = {.Luminosity = luminosity_val};
        return {MEASUREMENT_TYPE_LUMINOSITY, Data};
    }

    /**
     * @brief Sets the analog output value.
     *
     * This function initializes a Measurement_t structure with a scaled analog output value
     * and sets the measurement type to MEASUREMENT_TYPE_ANALOG_OUTPUT. The analog output value
     * is scaled by a factor of 100 to convert it from a float to a uint16_t for digital representation.
     * It is designed for controlling analog output devices or interfaces.
     *
     * @param analog_output_val The analog output value to set, as a floating-point number.
     *        This value is scaled by 100 to facilitate digital representation without losing precision.
     * @return Measurement_t A Measurement_t structure initialized with the scaled analog output value
     *         and the type set to MEASUREMENT_TYPE_ANALOG_OUTPUT.
     */
    static inline Measurement_t SetAnalogOutput(const float analog_output_val)
    {
        MeasurementData_t Data = {.AnalogGPIO = uint16_t((analog_output_val * 100))};
        return { MEASUREMENT_TYPE_ANALOG_OUTPUT, Data};
    }

    /**
     * @brief Sets the analog input value.
     *
     * This function initializes a Measurement_t structure with a scaled analog input value
     * and sets the measurement type to MEASUREMENT_TYPE_ANALOG_INPUT. The analog input value
     * is scaled by a factor of 100 to convert it from a float to a uint16_t for digital representation.
     * It is used for capturing or simulating analog sensor readings.
     *
     * @param analog_input_val The analog input value to set, as a floating-point number.
     *        This value is scaled by 100 to facilitate digital representation without losing precision.
     * @return Measurement_t A Measurement_t structure initialized with the scaled analog input value
     *         and the type set to MEASUREMENT_TYPE_ANALOG_INPUT.
     */
    static inline Measurement_t SetAnalogInput(const float analog_input_val)
    {
        MeasurementData_t Data = {.AnalogGPIO = uint16_t((analog_input_val * 100))};
        return { MEASUREMENT_TYPE_ANALOG_INPUT, Data};
    }

    /**
     * @brief Sets the temperature value.
     *
     * This function initializes a Measurement_t structure with a scaled temperature value
     * and sets the measurement type to MEASUREMENT_TYPE_TEMPERATURE. The temperature value
     * is scaled by a factor of 10 to convert it from a float to a uint16_t, allowing for a
     * fraction of a degree precision in digital representation.
     * It is used for temperature monitoring applications.
     *
     * @param temperature_val The temperature value to set, as a floating-point number.
     *        This value is scaled by 10 to provide a precision of 0.1 degrees in its digital form.
     * @return Measurement_t A Measurement_t structure initialized with the scaled temperature value
     *         and the type set to MEASUREMENT_TYPE_TEMPERATURE.
     */
    static inline Measurement_t SetTemperature(const float temperature_val)
    {
        MeasurementData_t Data = {.Temperature = uint16_t(temperature_val * 10)};
        return { MEASUREMENT_TYPE_TEMPERATURE, Data};
    }

    /**
     * @brief Sets the relative humidity value.
     *
     * This function initializes a Measurement_t structure with a scaled relative humidity value
     * and sets the measurement type to MEASUREMENT_TYPE_RELATIVE_HUMIDITY. The humidity value
     * is scaled by a factor of 2 to convert it from a float to a uint16_t, aiming to maintain
     * precision while accommodating the data type.
     * It is used for humidity monitoring in environmental control systems.
     *
     * @param humidity_val The relative humidity value to set, as a floating-point number.
     *        This value is scaled by 2 to adjust for the digital representation.
     * @return Measurement_t A Measurement_t structure initialized with the scaled relative humidity value
     *         and the type set to MEASUREMENT_TYPE_RELATIVE_HUMIDITY.
     */
    static inline Measurement_t SetRelativeHumidity(const float humidity_val)
    {
        MeasurementData_t Data = {.RelativeHumidity = uint16_t(humidity_val * 2)};
        return { MEASUREMENT_TYPE_RELATIVE_HUMIDITY, Data};
    }

    /**
     * @brief Sets the barometric pressure value.
     *
     * This function initializes a Measurement_t structure with a scaled barometric pressure value
     * and sets the measurement type to MEASUREMENT_TYPE_BAROMETRIC_PRESSURE. The pressure value
     * is scaled by a factor of 10 to convert it from a float to a uint16_t, providing a precision
     * of 0.1 hPa (hectopascals) in its digital representation.
     * It is used for atmospheric pressure monitoring in weather stations or environmental monitoring systems.
     *
     * @param barometric_pressure_val The barometric pressure value to set, as a floating-point number.
     *        This value is scaled by 10 to provide a precision of 0.1 hPa.
     * @return Measurement_t A Measurement_t structure initialized with the scaled barometric pressure value
     *         and the type set to MEASUREMENT_TYPE_BAROMETRIC_PRESSURE.
     */
    static inline Measurement_t SetBarometricPressure(const float barometric_pressure_val)
    {
        MeasurementData_t Data = {.BarometricPressure = uint16_t(barometric_pressure_val * 10)};
        return { MEASUREMENT_TYPE_BAROMETRIC_PRESSURE, Data};
    }

    /**
     * @brief Sets the acceleration values for the x, y, and z axes.
     *
     * This function initializes a Measurement_t structure with scaled acceleration values
     * and sets the measurement type to MEASUREMENT_TYPE_ACCELERATION. The acceleration values
     * are scaled by a factor of 1000 to convert them from floats to uint16_t, providing milli-g
     * precision in their digital representation. It is used for capturing or simulating acceleration
     * in various axes, typically in motion or orientation detection applications.
     *
     * @param x The acceleration value along the x-axis.
     * @param y The acceleration value along the y-axis.
     * @param z The acceleration value along the z-axis.
     *        These values are scaled by 1000 for precise milli-g representation.
     * @return Measurement_t A Measurement_t structure initialized with the scaled acceleration values
     *         and the type set to MEASUREMENT_TYPE_ACCELERATION.
     */
    static inline Measurement_t SetAcceleration(const float x, const float y, const float z)
    {
        const AcceleroVal_t accelero_val = {.x = uint16_t(x * 1000), .y = uint16_t(y * 1000), .z = uint16_t(z * 1000)};
        const MeasurementData_t Data = {.Acceleration = accelero_val};
        return { MEASUREMENT_TYPE_ACCELERATION, Data};
    }

    /**
     * @brief Sets the gyroscopic values for the x, y, and z axes.
     *
     * This function initializes a Measurement_t structure with scaled gyroscopic values
     * and sets the measurement type to MEASUREMENT_TYPE_GYRO. The gyro values
     * are scaled by a factor of 100 to convert them from floats to uint16_t, aiming to maintain
     * precision for angular velocity measurements. It is typically used in orientation and rotation
     * detection systems.
     *
     * @param x The gyro value along the x-axis.
     * @param y The gyro value along the y-axis.
     * @param z The gyro value along the z-axis.
     *        These values are scaled by 100 for digital representation.
     * @return Measurement_t A Measurement_t structure initialized with the scaled gyro values
     *         and the type set to MEASUREMENT_TYPE_GYRO.
     */
    static inline Measurement_t SetGyro(const float x, const float y, const float z)
    {
        const GyroVal_t gyro_val = {.x = uint16_t(x * 100), .y = uint16_t(y * 100), .z = uint16_t(z * 100)};
        const MeasurementData_t Data = {.Gyro = gyro_val};
        return { MEASUREMENT_TYPE_GYRO, Data};
    }

    /**
     * @brief Sets the GPS coordinates and altitude.
     *
     * This function initializes a Measurement_t structure with scaled GPS coordinate and altitude values
     * and sets the measurement type to MEASUREMENT_TYPE_GPS. The latitude and longitude values are scaled
     * by a factor of 10000, and the altitude by 100, converting them from floats to uint32_t for precise
     * geographic positioning. It is used for tracking and navigation applications.
     *
     * @param latitude The latitude value in degrees.
     * @param longitude The longitude value in degrees.
     * @param altitude The altitude value in meters.
     *        The latitude and longitude are scaled by 10000, and altitude by 100, for precise representation.
     * @return Measurement_t A Measurement_t structure initialized with the scaled GPS values
     *         and the type set to MEASUREMENT_TYPE_GPS.
     */
    static inline Measurement_t SetGPS(const float latitude, const float longitude, const float altitude)
    {
        const GPSCoord_t gps_val = {.latitude = uint32_t(latitude * 10000), .longitude = uint32_t(longitude * 10000), .altitude = uint32_t(altitude * 100)};
        const MeasurementData_t Data = {.GPS = gps_val};
        return { MEASUREMENT_TYPE_GPS, Data};
    }
    /**
     * @brief Sets a raw bit value in a measurement.
     *
     * This function updates the provided measurement with a new bit value, setting or
     * appending it based on the previous measurement's type. It is used to incrementally
     * build up a raw bit measurement from individual bits.
     *
     * @param raw_bit_val The raw bit value to set or append. Only the least significant bit is used.
     * @param prevMeasurement Reference to the previous measurement which will be updated
     *        with the new bit value.
     * @return Measurement_t The updated measurement with the new bit value set or appended.
     */
    static inline Measurement_t SetRawBit(const uint8_t raw_bit_val, Measurement_t &prevMeasurement)
    {
        const uint8_t prevMeasurementWasBit = (prevMeasurement.type >= MEASUREMENT_TYPE_RAWBIT_1 && prevMeasurement.type < MEASUREMENT_TYPE_RAWBIT_8);
        uint8_t bitpos = prevMeasurementWasBit ? ((prevMeasurement.type - MEASUREMENT_TYPE_RAWBIT_1) + 1): 0;
        if (prevMeasurementWasBit)
        {
            prevMeasurement.val.RawBit |= (raw_bit_val << bitpos);
            bitpos++;
            prevMeasurement.type = static_cast<CayenneMeasurementType_t>((MEASUREMENT_TYPE_RAWBIT_1 + bitpos) - 1);
        }
        else
        {
            prevMeasurement.val.RawBit = (raw_bit_val << bitpos);
            prevMeasurement.type = MEASUREMENT_TYPE_RAWBIT_1;
        }
        return prevMeasurement;
    }

    /**
     * @brief Sets a raw byte value in a measurement.
     *
     * This function initializes a Measurement_t structure with a raw byte value
     * and sets the measurement type to MEASUREMENT_TYPE_RAWBYTE. It is used for handling
     * raw byte data in various data communication or storage scenarios.
     *
     * @param raw_byte_val The raw byte value to set.
     * @return Measurement_t A Measurement_t structure initialized with the raw byte value
     *         and the type set to MEASUREMENT_TYPE_RAWBYTE.
     */
    static inline Measurement_t SetRawByte(const uint8_t raw_byte_val)
    {
        const RawByteVal_t raw_byte = raw_byte_val;
        const MeasurementData_t Data = {.RawByte = raw_byte};
        return { MEASUREMENT_TYPE_RAWBYTE, Data};
    }

    /**
     * @brief Sets a 16-bit word value in a measurement.
     *
     * This function initializes a Measurement_t structure with a 16-bit word value
     * and sets the measurement type to MEASUREMENT_TYPE_RAWWORD16. It is used for handling
     * 16-bit data in various scenarios, such as digital communication or sensor data encoding.
     *
     * @param word16_val The 16-bit word value to set.
     * @return Measurement_t A Measurement_t structure initialized with the 16-bit word value
     *         and the type set to MEASUREMENT_TYPE_RAWWORD16.
     */
    static inline Measurement_t SetWord16(const uint16_t word16_val)
    {
        const Word16Val_t word16 = word16_val;
        const MeasurementData_t Data = {.Word16 = word16};
        return { MEASUREMENT_TYPE_RAWWORD16, Data};
    }

    /**
     * @brief Sets a 32-bit word value in a measurement.
     *
     * This function initializes a Measurement_t structure with a 32-bit word value
     * and sets the measurement type to MEASUREMENT_TYPE_RAWWORD32. It is used for handling
     * 32-bit data in various applications, including data communication and sensor data processing.
     *
     * @param word32_val The 32-bit word value to set.
     * @return Measurement_t A Measurement_t structure initialized with the 32-bit word value
     *         and the type set to MEASUREMENT_TYPE_RAWWORD32.
     */
    static inline Measurement_t SetWord32(const uint32_t word32_val)
    {
        const Word32Val_t word32 = word32_val;
        const MeasurementData_t Data = {.Word32 = word32};
        return { MEASUREMENT_TYPE_RAWWORD32, Data};
    }

    /**
     * @brief Sets a 32-bit floating-point value in a measurement.
     *
     * This function initializes a Measurement_t structure with a 32-bit floating-point value
     * and sets the measurement type to MEASUREMENT_TYPE_RAWFLOAT32. It is particularly used for handling
     * floating-point data in scenarios where precise numerical values are essential, such as in scientific
     * measurements or complex data processing tasks.
     *
     * @param float32_val The 32-bit floating-point value to set.
     * @return Measurement_t A Measurement_t structure initialized with the 32-bit floating-point value
     *         and the type set to MEASUREMENT_TYPE_RAWFLOAT32.
     */
    static inline Measurement_t SetFloat32(const float float32_val)
    {
        const Float32Val_t float32 = float32_val;
        const MeasurementData_t Data = {.Float32 = float32};
        return { MEASUREMENT_TYPE_RAWFLOAT32, Data};
    }
}
#endif
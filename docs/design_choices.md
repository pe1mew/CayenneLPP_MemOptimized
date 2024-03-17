# Design choices

As you might have noticed, this library is very similar to the original [CayenneLPP](https://github.com/myDevicesIoT/CayenneLPP) encoder library. That is because this library is based up on the original CayenneLPP library, but some things were altered to make it more performant/memory optimized.

## What has been added?
- CMake support (Standalone library compilation, as well for the compilation of the tests!)
- PlatformIO support (For cross-compilation on many targets (this library has no mcu specific dependencies!))
- Unit tests
- Raw types (such as bits, byte, 16-bit word, 32-bit word, 32-bit float)
- Arduino examples
- More documentation
- Usage of Namespaces to prevent Namespace pollution

## What has been removed?
- The dynamic memory allocation (in the constructor) has been removed and replaced with template class, which initializes buffer at compile-time.
- The helper functions inside the CayenneLPP class which add specific types in to the buffer, the helper functions are now moved out of the class.
- General optimizations (such as the usage of memcpy instead of raw loop copying)

## Why and How?

The project client asked us to optimize the library, being a software developer himself had some requirements which had to be met:

- Decrease the Flash & RAM usage of the original CayenneLPP library on the AVR platform

- A subset of the functions inside the original CayenneLPP class should be kept 
    - CayenneLPP(size_t size)
    - void reset(void);
    - uint8_t getSize(void);
    - uint8_t *getBuffer(void);

- Support the Arduino ecosystem and publish it as an Arduino library

- Setters should be used

### Keeping the original protocol format

The original frame format off the CayenneLPP protocol was kept, there are ways to make it more efficient. But these ways seem to sacrifice generic usage of the protocol for efficiency. Meaning that the protocol then becomes application specific using protobuffer for example or has no channel functionality/type recognition.

### Removing the original setters

The original library used setters for all the different types (setTemperature(...), setHumidity(...), etc.), which meant that the functions were always included in the binary even when they were not used. 

```cpp

class CayenneLPP {
    public:
        ...        
        uint8_t addDigitalInput(uint8_t channel, uint8_t value);
        uint8_t addDigitalOutput(uint8_t channel, uint8_t value);
        ...   
};
```

To help the compiler optimize unused functions away (thus saving flash usage), we decided that moving these setters outside of the class was a better idea. But then these outside methods have to somehow add the measurement to the CayenneEncoder buffer, to mitigate this issue a `Measurement_t` struct was added.

This Measurement_t struct contains the value to be added to the encoder buffer and the MeasurementType (so the decoder on the other end knows how to parse the value correctly). 

```cpp title="CayenneTypes.hpp - a portion of :)"
typedef enum
{
    MEASUREMENT_TYPE_DIGITAL_OUTPUT = 1,
    MEASUREMENT_TYPE_DIGITAL_INPUT = 0,
    ...
} CayenneMeasurementType_t;

typedef union
{
    DigitalGPIOVal_t DigitalGPIO;
    ...
    uint8_t RawBytes[CAYENNE_MAX_UNION_SIZE];
} MeasurementData_t;

typedef struct
{
    CayenneMeasurementType_t type;
    MeasurementData_t val;
} Measurement_t;

static inline Measurement_t SetDigitalOutput(const uint8_t digital_output_val)
{
    MeasurementData_t Data = {.DigitalGPIO = digital_output_val};
    return {MEASUREMENT_TYPE_DIGITAL_OUTPUT, Data};
}

static inline Measurement_t SetDigitalInput(const uint8_t digital_input_val)
{
    MeasurementData_t Data = {.DigitalGPIO = digital_input_val};
    return {MEASUREMENT_TYPE_DIGITAL_INPUT, Data};
}
```
And the encoder class now has a `setMeasurement()` function to add the measurement to the CayenneEncoder buffer:

```cpp title="CayenneLPP.hpp - Encoder class"
template <size_t static_size>
class CayenneLPP
{
   public:
   ...
   const uint8_t setMeasurement(const uint8_t channel, 
                                const Measurement_t measurement);
};
```

**This change proved to save around ~20% of flash when reusing the same `Measurement_t` struct and adding more than two measurements!**


### CMake and PlatformIO buildsystem support
Arduino IDE is great for quick prototyping, but eventually you would maybe like to use it in a toolchain/project where Arduino might not be the best choice! That is where CMake and PlatformIO come in! Here you can easily add this library to the dependencies of your project and it will compile just like it does on Arduino. Besides this the Arduino IDE does not have compatibility for Unit testing yet, thus another build system was needed to help compile the tests.

### Raw types
The original library did not have support for sending raw data_types such as float32, word32, word16, bytes and bits. Which are useful when sending raw sensor values which are not implemented in the CayenneLPP encoder/decoder library.

### Other General improvements
Inside the original class setters where loops like these:
```cpp
for (uint8_t i=0; i < amount_of_bytes; i++) {
    internal_buf[i] = temp_buf[i];
}
```
These are raw copy loops, although not necessarily evil, more performance can sometimes be achieved by using the c stdlib function for this. As these functions are sometimes optimized by the MCU manufacturer for the architecture used, if not it results in an old fashioned for loop anyways. Thus there is no performance lost anyways:
```cpp
memcpy(internal_buf, temp_buf, amount_of_bytes);
```
---
Besides this, namespaces are used to isolate enum values and typenames from reaching polluting other sections of the program:
```cpp
namespace CayenneLPP {
    ...
}
```

# Library API

This section will describe the API of this library.

## Payload encoder

The public API of the encoder class has these functions available:

```cpp
namespace CayenneLPP
{

    template <size_t static_size>
    class CayenneLPP
    {
    public:
        /**
         * \brief Constructor, this class is now a template class 
         *         and supposed to be initialized with template syntax.
         * \example Initialize like this: 
         *          CayenneLPP::CayenneLPP<100> enc_inst;
         *          Please note that this reserves a buffer of 100 bytes,
         *          you are free to go higher or lower, but keep in mind that
         *          a GPS measurement is the largest measurement and takes atleast 11-bytes to store.
        */
        CayenneLPP();

        /**
         * \brief Since this class is initialized statically, there is nothing to clean up.
        */
        ~CayenneLPP();

        /**
         * \brief Reset the cursor back to zero.
        */
        void reset(void);

        /**
         * \brief This gets the amount of bytes currently stored in the buffer
         * \return The amount of bytes stored
        */
        constexpr uint8_t getSize(void);

        /**
         * \brief This gets a pointer to the statically allocated internal buffer
         * \return Pointer to the buffer
        */
        constexpr uint8_t *getBuffer(void);

        /**
         * \brief Store a new measurement in the encoder buffer
         * \return The cursor position in the internal buffer
        */
        const uint8_t setMeasurement(const uint8_t channel, 
                                     const Measurement_t *measurement);       
    };
}
```

### Reset function
```cpp
void CayenneLPP::reset(void);
```
The Reset function will reset the internal buffer byte counter to zero. If elements are added to the buffer after a call to reset, previous elements will be overwritten.

#### Error checking

This function does not have error checking! As the buffer is statically assigned and no parameters are entered in to this function, error checking is not needed.

#### Parameters
This function does not accept parameters!


#### Return
This function returns `void`.

!!! warning "The buffer will not be emptied!"

    Please note that a call to reset will not empty buffer, it will only reset the counter to zero! All the old data will still be in the buffer after the reset call.

#### Usage
The function can be used by first initializing the class and then calling the reset() function:
```cpp
#include <CayenneLPP.hpp>
#define BUF_SIZE 100
void main(){
    CayenneLPP::CayenneLPP<BUF_SIZE> encoder;
    
    encoder.reset();
}
```

### getSize function
```cpp
constexpr uint8_t CayenneLPP::getSize(void);
```
The getSize function will return the current amount of bytes stored in the buffer. 

#### Error checking
This function does not have error checking! As the buffer is statically assigned and no parameters are entered in to this function, error checking is not needed.

#### Parameters
This function does not accept parameters!

#### Return
This function returns the currently written amount of bytes in `uint8_t` format.

#### Usage
The function can be used by first initializing the class and then calling the getSize() function:
```cpp
#include <CayenneLPP.hpp>
#define BUF_SIZE 100
void main(){
    CayenneLPP::CayenneLPP<BUF_SIZE> encoder;
    
    uint8_t size = encoder.getSize();
    /* size should be 0, as the encoder has just been initialized */
    Serial.println(size);
}
```

### getBuffer function
```cpp
constexpr uint8_t* CayenneLPP::getBuffer(void);
```
The getBuffer function will return a pointer to the internal statically assigned buffer!

#### Error checking
This function does not have error checking! As the buffer is statically assigned and no parameters are entered in to this function, error checking is not needed.

#### Parameters
This function does not accept parameters!

#### Return
This function returns a pointer to the internal statically assigned buffer in `uint8_t *` format.

#### Usage
The function can be used by first initializing the class and then calling the getBuffer() function:
```cpp
#include <CayenneLPP.hpp>
#define BUF_SIZE 100
void main(){
    CayenneLPP::CayenneLPP<BUF_SIZE> encoder;
    
    uint8_t* buffer = encoder.getBuffer();
    /* Should print nothing, as the buffer is empty! */
    Serial.println(buffer);
}
```

### setMeasurement function
```cpp
const uint8_t CayenneLPP::setMeasurement(const uint8_t channel,
                                         const Measurement_t *measurement);
```
The setMeasurement() function will store a new measurement inside the internal encoder buffer.

#### Error checking
This function does dynamically error checks on the internal encoder buffer and the incoming parameters.

#### Parameters
This function accepts a `channel` and `measurement` parameter.

#### Return
This function returns the current buffer counter position.

#### Usage
The function can be used by first initializing the class and then calling the setMeasurement() function:
```cpp
#include <CayenneLPP.hpp>
#define BUF_SIZE 100
#define CHANNEL 1
void main(){
    CayenneLPP::CayenneLPP<BUF_SIZE> encoder;
    
    CayenneLPP::Measurement_t measurement = CayenneLPP::SetDigitalOutput(1);

    encoder.setMeasurement(1, measurement); 
}
```

## Measurement functions

The `Measurement_t` struct can be used without these functions, though it helps to use these functions as they do not introduce a run-time and space cost (as they are inline).

```cpp
namespace CayenneLPP
{
    static inline Measurement_t SetDigitalOutput(const uint8_t digital_output_val);

    static inline Measurement_t SetDigitalInput(const uint8_t digital_input_val);

    static inline Measurement_t SetPresence(const uint8_t presence_val);

    static inline Measurement_t SetLuminosity(const uint16_t luminosity_val);

    static inline Measurement_t SetAnalogOutput(const float analog_output_val);

    static inline Measurement_t SetAnalogInput(const float analog_input_val);

    static inline Measurement_t SetTemperature(const float temperature_val);

    static inline Measurement_t SetRelativeHumidity(const float humidity_val);

    static inline Measurement_t SetBarometricPressure(const float barometric_pressure_val);

    static inline Measurement_t SetAcceleration(const float x, 
                                                const float y, 
                                                const float z);

    static inline Measurement_t SetGyro(const float x, 
                                        const float y, 
                                        const float z);
    
    static inline Measurement_t SetGPS(const float latitude, 
                                       const float longitude, 
                                       const float altitude);
    
    static inline Measurement_t SetRawBit(const uint8_t raw_bit_val,            
                                          Measurement_t &prevMeasurement);
    
    static inline Measurement_t SetRawByte(const uint8_t raw_byte_val);

    static inline Measurement_t SetWord16(const uint16_t word16_val);

    static inline Measurement_t SetWord32(const uint32_t word32_val);

    static inline Measurement_t SetFloat32(const float float32_val);
}
```

### Usage

All these functions are used the same way **except for the `SetRawBit` function**.

First initialize an empty `Measurement_t` struct and then call the Set... function to fill that struct with your required measurement:

```cpp
#include <CayenneLPP.hpp>

void main() {
    CayenneLPP::Measurement_t measurement;

    measurement = CayenneLPP::SetDigitalOutput(1);
}
```
The `Measurement_t` instance can then be reused when added to the encoder buffer:

``` cpp
#include <CayenneLPP.hpp>
#define BUF_SIZE 100
#define DIGITAL_TRANSMIT_CH 0
#define ANALOG_TRANSMIT_CH 1

void main() {
    CayenneLPP::CayenneLPP<BUF_SIZE> encoder;
    CayenneLPP::Measurement_t measurement;

    measurement = CayenneLPP::SetDigitalOutput(1);

    encoder.setMeasurement(DIGITAL_TRANSMIT_CH, &measurement);

    measurement = CayenneLPP::SetAnalogOutput(2.3);

    encoder.setMeasurement(ANALOG_TRANSMIT_CH, &measurement);
}
```

### Usage of the SetRawBit function

The `SetRawBit` function requires one additional step to use, compared to the other helper functions.
It needs the old version of the measurement struct passed in to the parameters:

``` cpp
#include <CayenneLPP.hpp>
#define BUF_SIZE 100
#define DIGITAL_TRANSMIT_CH 0
#define ANALOG_TRANSMIT_CH 1

void main() {
    CayenneLPP::CayenneLPP<BUF_SIZE> encoder;
    CayenneLPP::Measurement_t measurement;
    
    CayenneLPP::SetRawBit(1, &measurement);
}
```

Now the real party trick! Adding more bits...

``` cpp
#include <CayenneLPP.hpp>
#define BUF_SIZE 100
#define DIGITAL_TRANSMIT_CH 0
#define ANALOG_TRANSMIT_CH 1

void main() {
    CayenneLPP::CayenneLPP<BUF_SIZE> encoder;
    CayenneLPP::Measurement_t measurement;

    for(uint8_t i = 0; i < 8; i++) {
        const uint8_t bit_to_set = (i % 2); // Modulo 2 as example, 
                                            // could be digitalread
        CayenneLPP::SetRawBit(bit_to_set, &measurement);
    }
}
```
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
                                     const Measurement_t measurement);       
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
                                         const Measurement_t measurement);
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
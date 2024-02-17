#ifndef _CAYENNE_LPP_H_
#define _CAYENNE_LPP_H_
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "CayenneTypes.hpp"
namespace CayenneLPP
{

    template <size_t static_size>
    class CayenneLPP
    {
    public:
        constexpr CayenneLPP(size_t size = static_size)
        {
            maxsize = size;
            reset();
        }

        ~CayenneLPP()
        {
        }

        void reset(void)
        {
            cursor = 0;
        }

        constexpr uint8_t getSize(void)
        {
            return cursor;
        }
        uint8_t *getBuffer(void)
        {
            return buffer;
        }

        const uint8_t setMeasurement(const uint8_t channel, const Measurement_t measurement)
        {
            const size_t measurement_size = DetermineMeasurementSize(measurement.type);
            size_t new_cursor_pos = (cursor + measurement_size + 2);
            if (new_cursor_pos > maxsize)
            {
                return 0;
            }
            buffer[cursor++] = channel;
            buffer[cursor++] = measurement.type;
            memcpy((buffer + cursor), measurement.val.RawBytes, measurement_size);
            return cursor;
        }
        uint8_t copy(uint8_t *dst)
        {
            memcpy(dst, buffer, cursor);
            return cursor;
        }

    private:
        const uint8_t DetermineMeasurementSize(const CayenneMeasurementType_t type)
        {
            switch (type)
            {
            case MEASUREMENT_TYPE_DIGITAL_OUTPUT:
            case MEASUREMENT_TYPE_DIGITAL_INPUT:
            case MEASUREMENT_TYPE_PRESENCE:
            case MEASUREMENT_TYPE_RAWBYTE:
            case MEASUREMENT_TYPE_RAWBIT_1:
            case MEASUREMENT_TYPE_RAWBIT_2:
            case MEASUREMENT_TYPE_RAWBIT_3:
            case MEASUREMENT_TYPE_RAWBIT_4:
            case MEASUREMENT_TYPE_RAWBIT_5:
            case MEASUREMENT_TYPE_RAWBIT_6:
            case MEASUREMENT_TYPE_RAWBIT_7:
            case MEASUREMENT_TYPE_RAWBIT_8:
            {
                return sizeof(DigitalGPIOVal_t);
                break;
            }
            case MEASUREMENT_TYPE_RAWWORD16:
            case MEASUREMENT_TYPE_LUMINOSITY:
            case MEASUREMENT_TYPE_ANALOG_OUTPUT:
            case MEASUREMENT_TYPE_ANALOG_INPUT:
            case MEASUREMENT_TYPE_TEMPERATURE:
            case MEASUREMENT_TYPE_RELATIVE_HUMIDITY:
            case MEASUREMENT_TYPE_BAROMETRIC_PRESSURE:
            {
                return sizeof(AnalogGPIOVal_t);
                break;
            }
            case MEASUREMENT_TYPE_RAWWORD32:
            case MEASUREMENT_TYPE_RAWFLOAT32:
            {
                return sizeof(Float32Val_t);
                break;
            }

            case MEASUREMENT_TYPE_GPS:
            {
                return sizeof(CayenneGPSCoord_t);
                break;
            }
            default:
            {
                return 1;
                break;
            }
            }
            return 1;
        }
        uint8_t buffer[static_size];
        uint8_t maxsize;
        uint8_t cursor;
    };
}
#endif
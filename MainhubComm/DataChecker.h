#ifndef __DATACHECKER_H__
#define __DATACHECKER_H__

#include <cstdint>
#include <iostream>

class DataChecker
{
    public:
        DataChecker() = default;
        virtual ~DataChecker() = default;
        /**
         * Starts a new 9 bit Cyclic Redundancy Check (CRC-8) calculation.
         * 
         * @param data      byte array
         * @param length    number of bytes
         * @return uint8_t  crc
         */
        uint8_t calc(uint8_t *data, unsigned int length);

        /**
         * Feed more data in the CRC calculation. calc() must
         * be called the first time, before using update()
         * multiple times.
         * 
         * @param data      byte array
         * @param length    number of bytes
         * @return uint8_t  crc
         */
        uint8_t update(uint8_t *data, unsigned int length);

    private:
        uint8_t _seed = 0;
};

#endif // __DATACHECKER_H__
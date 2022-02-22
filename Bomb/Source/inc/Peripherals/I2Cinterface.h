//
// Created by david on 19-5-19.
//

#ifndef MAIN_BOM_I2CINTERFACE_H
#define MAIN_BOM_I2CINTERFACE_H

#include <string>

namespace Peripherals
{
    class I2Cinterface
    {
    public:
        explicit I2Cinterface(std::string device);
        virtual ~I2Cinterface();

    public:
        void Write(uint8_t address, uint8_t value);
        void Write(uint8_t address, uint8_t reg, uint8_t value);
        void Write(uint8_t address, uint8_t *value, uint8_t size);

        uint8_t Read(uint8_t address);
        uint8_t Read(uint8_t address, uint8_t reg);
        void Read(uint8_t address, uint8_t *buffer, uint8_t size);
        void Read(uint8_t address, uint8_t reg, uint8_t *buffer, uint8_t size);

    private:
        int m_fd;

    private:
        void SetAddress(uint8_t address);
    };
};

#endif // MAIN_BOM_I2CINTERFACE_H

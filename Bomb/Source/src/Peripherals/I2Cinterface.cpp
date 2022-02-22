//
// Created by david on 19-5-19.
//

#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "Peripherals/I2Cinterface.h"

Peripherals::I2Cinterface::I2Cinterface(std::string device)
    : m_fd(0)
{
    m_fd = open(device.c_str(), O_RDWR);

    if (m_fd < 0)
        throw "Unable to open I2C";
}

Peripherals::I2Cinterface::~I2Cinterface()
{
}

void Peripherals::I2Cinterface::Write(uint8_t address, uint8_t value)
{
    Write(address, &value, 1);
}

void Peripherals::I2Cinterface::Write(uint8_t address, uint8_t reg, uint8_t value)
{
    uint8_t buffer[2] = {reg, value};
    Write(address, buffer, 2);
}

void Peripherals::I2Cinterface::Write(uint8_t address, uint8_t *value, uint8_t size)
{
    SetAddress(address);

    if (write(m_fd, value, size) != size)
    {
        throw "I2C size mismatch (send more/less data then required)";
    }
}

uint8_t Peripherals::I2Cinterface::Read(uint8_t address)
{
    uint8_t buffer;

    Read(address, &buffer, 1);
    return buffer;
}

uint8_t Peripherals::I2Cinterface::Read(uint8_t address, uint8_t reg)
{
    Write(address, reg);
    return Read(address);
}

void Peripherals::I2Cinterface::Read(uint8_t address, uint8_t *buffer, uint8_t size)
{
    SetAddress(address);

    if (read(m_fd, buffer, size) != size)
    {
        throw "I2C size mismatch (read more/less data then required)";
    }
}

void Peripherals::I2Cinterface::Read(uint8_t address, uint8_t reg, uint8_t *buffer, uint8_t size)
{
    Write(address, reg);
    Read(address, buffer, size);
}

void Peripherals::I2Cinterface::SetAddress(uint8_t address)
{
    if (ioctl(m_fd, I2C_SLAVE, address) < 0)
    {
        throw "Unable to set I2C slave address";
    }
}

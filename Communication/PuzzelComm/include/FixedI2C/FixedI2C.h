#ifndef __FIXEDI2C_H__
#define __FIXEDI2C_H__

#ifdef ARDUINO_ARCH_ESP32

#include <stdint.h>
#include <driver/i2c.h>
#include <Stream.h>
#include "DataWrapper.h"
#include "DataUnwrapper.h"

#define I2C_BUFFER_LENGTH 128

class FixedI2C : public Stream
{
public:
    FixedI2C(uint8_t bus_num);
    ~FixedI2C();

    bool begin(int sda, int scl, int address);
    void update();

    size_t write(uint8_t);
    size_t write(const uint8_t *, size_t);
    int available(void);
    int read(void);
    int peek(void);
    void flush(void);

    inline size_t write(const char * s)
    {
        return write((uint8_t*) s, strlen(s));
    }
    inline size_t write(const uint8_t * s, uint16_t len)
    {
        return write(s, (size_t)len);
    }
    inline size_t write(unsigned long n)
    {
        return write((uint8_t)n);
    }
    inline size_t write(long n)
    {
        return write((uint8_t)n);
    }
    inline size_t write(unsigned int n)
    {
        return write((uint8_t)n);
    }
    inline size_t write(int n)
    {
        return write((uint8_t)n);
    }
    
    void onReceive(void (*)(int));
    void onRequest(void (*)());

private:
    uint8_t num;
    i2c_port_t portNum;
    int8_t sda;
    int8_t scl;

    uint8_t rxBuffer[I2C_BUFFER_LENGTH];
    uint16_t rxIndex;
    uint16_t rxLength;
    uint16_t rxQueued;

    uint8_t txBuffer[I2C_BUFFER_LENGTH];
    uint16_t txIndex;
    uint16_t txLength;
    uint16_t txAddress;
    uint16_t txQueued;

    void (*user_onRequest)(void);
    void (*user_onReceive)(int);

    DataWrapper _wrapper;
    DataUnwrapper _unwrapper;
};


extern FixedI2C FixedWire;
extern FixedI2C FixedWire1;

#endif      // ifdef ARDUINO_ARCH_ESP32

#endif // __FIXEDI2C_H__
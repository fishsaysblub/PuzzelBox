#ifdef ARDUINO_ARCH_ESP32
#include <Arduino.h>
#include <driver/i2c.h>

#include "FixedI2C/FixedI2C.h"

FixedI2C::FixedI2C(uint8_t bus_num)
    :num(bus_num & 1)
    ,portNum(i2c_port_t(bus_num & 1))
    ,sda(-1)
    ,scl(-1)
    ,rxIndex(0)
    ,rxLength(0)
    ,rxQueued(0)
    ,txIndex(0)
    ,txLength(0)
    ,txAddress(0)
    ,txQueued(0)
    ,_wrapper()
    ,_unwrapper()
{

}

FixedI2C::~FixedI2C()
{
    flush();
    i2c_driver_delete(portNum);
}


bool FixedI2C::begin(int sda, int scl, int address)
{
    i2c_config_t config;
    config.sda_io_num = gpio_num_t(sda);
    config.sda_pullup_en = GPIO_PULLUP_ENABLE;
    config.scl_io_num = gpio_num_t(scl);
    config.scl_pullup_en = GPIO_PULLUP_ENABLE;
    config.mode = I2C_MODE_SLAVE;
    config.slave.addr_10bit_en = 0;
    config.slave.slave_addr = address & 0x7F;

    esp_err_t res = i2c_param_config(portNum, &config);

    if (res != ESP_OK) 
    {
        Serial.println("invalid I2C parameters");
        return false;
    }

    res = i2c_driver_install(
            portNum,
            config.mode,
            2 * I2C_BUFFER_LENGTH,  // rx buffer length
            2 * I2C_BUFFER_LENGTH,  // tx buffer length
            0);

    if (res != ESP_OK) 
        Serial.println("failed to install I2C driver");

    return res == ESP_OK;
}

void FixedI2C::update()
{
    uint8_t inputBuffer[I2C_BUFFER_LENGTH] = {0};
    int16_t inputLen = 0;

    inputLen = i2c_slave_read_buffer(portNum, inputBuffer, I2C_BUFFER_LENGTH, 1);

    if (inputLen <= 0) 
    {
        // nothing received or error
        return;
    }
    Serial.print("recieved data[");
    Serial.print(inputLen);
    Serial.print("]\n");
    if (!_unwrapper.isPacketOpen()) 
    {
        // start unpacking
        _unwrapper.reset();
    }

    _unwrapper.write(inputBuffer, size_t(inputLen));

    if (_unwrapper.isPacketOpen() || _unwrapper.totalLength() == 0) 
    {
        Serial.println("open or empty");
        // still waiting bytes,
        // or received bytes that are not inside a packet
        return;
    }

    if (_unwrapper.hasError()) 
    {
        Serial.print("Receive has error[");
        Serial.print(_unwrapper.hasError());
        Serial.print("]\n");
        
        return;
    }
    if (_unwrapper.available()) 
    {
        rxIndex = 0;
        rxLength = _unwrapper.available();

        // transfer bytes from packet to rxBuffer
        while (_unwrapper.available()) 
        {
            rxBuffer[rxIndex] = _unwrapper.read();
            rxIndex += 1;
        }
        rxIndex = 0;

        // call user callback
        if (user_onReceive) 
            user_onReceive(rxLength);

    }
    else if (user_onRequest) 
    {
        txIndex = 0;
        txLength = 0;
        _wrapper.reset();
        user_onRequest();
        _wrapper.end();

        while (_wrapper.available()) 
        {
            txBuffer[txIndex] = _wrapper.read();
            txIndex +=1;
        }
        txLength = txIndex;

        i2c_reset_tx_fifo(portNum);
        i2c_slave_write_buffer(portNum, txBuffer, txLength, 0);
    }
}

size_t FixedI2C::write(uint8_t data)
{
    if (_wrapper.packetLength() >= I2C_BUFFER_LENGTH) 
        return 0;

    return _wrapper.write(data);
}

size_t FixedI2C::write(const uint8_t *data, size_t quantity)
{
    for (size_t i = 0; i < quantity; ++i) 
    {
        if (!write(data[i])) 
            return i;
    }

    return quantity;
}

int FixedI2C::available(void) { return rxLength - rxIndex; }

int FixedI2C::read(void)
{
    int value = -1;
    if(rxIndex < rxLength) 
    {
        value = rxBuffer[rxIndex];
        rxIndex += 1;
    }
    return value;
}

int FixedI2C::peek(void)
{
    int value = -1;
    
    if(rxIndex < rxLength) 
        value = rxBuffer[rxIndex];

    return value;
}

void FixedI2C::flush(void)
{
    rxIndex = 0;
    rxLength = 0;
    txIndex = 0;
    txLength = 0;
    rxQueued = 0;
    txQueued = 0;
    i2c_reset_rx_fifo(portNum);
    i2c_reset_tx_fifo(portNum);
}

void FixedI2C::onReceive(void (*function)(int))
{
    user_onReceive = function;
}

void FixedI2C::onRequest(void (*function)(void))
{
    user_onRequest = function;
}

FixedI2C FixedWire = FixedI2C(0);
FixedI2C FixedWire1 = FixedI2C(1);

#endif      // ifdef ARDUINO_ARCH_ESP32
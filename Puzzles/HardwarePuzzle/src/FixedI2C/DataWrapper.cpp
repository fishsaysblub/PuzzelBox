#include "FixedI2C/DataWrapper.h"
#include "FixedI2C/DataChecker.h"

DataWrapper::DataWrapper() { reset(); }

size_t DataWrapper::write(uint8_t data)
{
    if (!_is_packet_open) {
        return 0;
    }

    // leave room for crc and end bytes
    if (_is_packet_open >= PACKER_BUFFER_LENGTH - 2) {
        return 0;
    }

    _buffer[_index] = data;
    ++_index;
    _total_length = _index;

    return 1;
}

size_t DataWrapper::write(const uint8_t *data, size_t quantity)
{
    for (size_t i = 0; i < quantity; ++i) {
        if (!write(data[i])) {
            return i;
        }
    }
    return quantity;
}

void DataWrapper::end()
{
    _is_packet_open = false;

    // make room for CRC byte
    ++_index;

    _buffer[_index] = FRAME_END;
    ++_index;
    _total_length = _index;

    _buffer[1] = _total_length;

    // ignore start, length, crc and end bytes
    uint8_t payloadLength = _total_length - 4;

    DataChecker crc8;
    crc8.calc(&_total_length, 1);   // include length in CRC
    uint8_t crc = crc8.update(_buffer + 2, payloadLength);
    _buffer[_index-2] = crc;

    // prepare for reading
    _index = 0;
}

size_t DataWrapper::available()
{
    if (_is_packet_open) {
        return 0;
    }

    return _total_length - _index;
}

int DataWrapper::read()
{
    int value = -1;

    if (!_is_packet_open && _index < _total_length) {
        value = _buffer[_index];
        ++_index;
    }
    
    return value;
}

void DataWrapper::reset()
{
    _buffer[0] = FRAME_START;
    _index = 2;
    _total_length = 2;
    _is_packet_open = true;
}


#ifdef PACKER_DEBUG

void DataWrapper::printToSerial()
{
    Serial.printf("length: %d, ", _total_length);

    if (_is_packet_open)
        Serial.print("open, ");
    else
        Serial.print("closed, ");
    
    if (_total_length > 2)
    {
        Serial.print("buffer str: '");

        for (size_t i = 0; i < _total_length; ++i) 
        {
            if (_buffer[i] < 32 || _buffer[i] >= 127)
                Serial.print(".");
            else
                Serial.print((char) _buffer[i]);
        }

        Serial.print("', buffer hex: ");

        for (size_t i = 0; i < _total_length; ++i) 
            Serial.printf("0x%02X ", _buffer[i]);
    }
    else 
    {
        Serial.print("empty");
    }

    Serial.println();
}

#endif      // ifdef PACKER_DEBUG
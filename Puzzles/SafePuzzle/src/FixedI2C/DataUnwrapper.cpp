#include "FixedI2C/DataUnwrapper.h"
#include "FixedI2C/DataChecker.h"

DataUnwrapper::DataUnwrapper()
    :_index(0)
    ,_total_length(0)
    ,_payload_length(0)
    ,_is_packet_open(false)
    ,_expected_length(0)
    ,_expected_crc(0)
    ,_last_error(DataUnwrapper::NONE)
{
}

size_t DataUnwrapper::write(uint8_t data)
{
    if (_total_length >= UNPACKER_BUFFER_LENGTH || hasError())
        return 0;

    if (!_is_packet_open) 
    {
        // enable writing only if buffer is empty
        if (_total_length == 0 && data == _frame_start) 
        {
            _is_packet_open = true;
            _total_length += 1;
            return 1;
        }
        return 0;
    }

    // first byte after start is packet length
    if (_expected_length == 0) 
    {
        _expected_length = data;

        if (_expected_length > UNPACKER_BUFFER_LENGTH) {
            _is_packet_open = false;
            Serial.println("Invalid length");
            _last_error = DataUnwrapper::INVALID_LENGTH;
            return 0;
        }

        _total_length += 1;
        return 1;
    }

    // if end byte index wasn't reached
    if (_total_length < (_expected_length - 1)) 
    {
        _buffer[_index] = data;
        _index += 1;
        _total_length += 1;
        return 1;
    }

    _is_packet_open = false;

    // add end byte
    _total_length += 1;

    if (data != _frame_end) 
    {
        Serial.print("Expected end frame [0x04] but got [");
        Serial.print(data);
        Serial.print("]\n");
        _last_error = DataUnwrapper::INVALID_LENGTH;
        return 0;
    }

    // ignore start, length, crc and end bytes
    _payload_length = _total_length - 4;

    DataChecker crc8;
    crc8.calc(&_expected_length, 1);     // add length to CRC
    uint8_t crc = crc8.update(_buffer, _payload_length);

    if (crc != _buffer[_index-1]) 
    {
        Serial.print("Expected Crc [");
        Serial.print(crc);
        Serial.print("]\n");

        Serial.print("Gotten Crc [");
        Serial.print( _buffer[_index-1]);
        Serial.print("]\n");

        _last_error = DataUnwrapper::INVALID_CRC;
        return 0;
    }
    _index = 0;
    return 1;
}

size_t DataUnwrapper::write(const uint8_t *data, size_t quantity)
{
    for (size_t i = 0; i < quantity; ++i) 
    {
        if (!write(data[i]))
            return i;
    }
    return quantity;
}

size_t DataUnwrapper::available(void)
{
    return _is_packet_open ? 0 : ( _payload_length - _index); 
}

int DataUnwrapper::read(void)
{
    int value = -1;
    if (!_is_packet_open && _index < _payload_length) 
    {
        value = _buffer[_index];
        _index += 1;;
    }
    return value;
}

#ifdef UNPACKER_DEBUG

void DataUnwrapper::printToSerial()
{
    Serial.printf("totalLen: %d, expectedLen: %d, ", _total_length, _expected_length);

    if (_is_packet_open) 
        Serial.print("open, ");
    else 
        Serial.print("closed, ");

    switch (_last_error) 
    {
        case DataUnwrapper::INVALID_CRC:
            Serial.print("invalid crc, ");
            break;
        case DataUnwrapper::INVALID_LENGTH:
            Serial.print("invalid length, ");
            break;
        default: ;
    }
    
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

#endif      // ifdef UNPACKER_DEBUG

void DataUnwrapper::reset()
{
    _index = 0;
    _total_length = 0;
    _expected_length = 0;
    _is_packet_open = false;
    _last_error = DataUnwrapper::NONE;
}
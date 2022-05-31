#include "DataUnwrapper.h"
#include "DataChecker.h"

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
            std::cout << "Invalid length" << std::endl;
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
        std::cout << "Expected end frame [0x04] but got [" << (int)data << "]" << std::endl;
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
        std::cout << "Expected crc[" << (int)crc << "]" << std::endl;
        std::cout << "Gotten crc[" << (int)_buffer[_index-1] << "]" << std::endl;
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
    std::cout << "total length[" << (int)_total_length << "], expectedLen [" <<
     _expected_length << "], ";

    if (_is_packet_open) 
        std::cout << "open, ";
    else 
       std::cout << "closed, ";

    switch (_last_error) 
    {
        case DataUnwrapper::INVALID_CRC:
            std::cout << "invalid crc, ";
            break;
        case DataUnwrapper::INVALID_LENGTH:
            std::cout << "invalid length, ";
            break;
        default: ;
    }
    
    if (_total_length > 2)
    {
        std::cout << "buffer str: '";

        for (size_t i = 0; i < _total_length; ++i) 
        {
            if (_buffer[i] < 32 || _buffer[i] >= 127)
                std::cout << ".";
            else
               std::cout << (char) _buffer[i];
        }

        std::cout << "', buffer hex: ";

        for (size_t i = 0; i < _total_length; ++i) 
           std::cout << "0x" << std::hex << (int)_buffer[i] << ", ";     
    }
    else 
    {
        std::cout << "empty";
    }

    std::cout << std::endl;
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
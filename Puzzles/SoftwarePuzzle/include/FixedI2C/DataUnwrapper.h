#ifndef __DATAUNWRAPPER_H__
#define __DATAUNWRAPPER_H__

#include <Arduino.h>

#define UNPACKER_BUFFER_LENGTH 128

#define UNPACKER_DEBUG

class DataUnwrapper
{
public:

    typedef enum e_Error : char
    {
        NONE = 0,
        INVALID_CRC,
        INVALID_LENGTH
    } Error;

    DataUnwrapper();
    
    /**
     * Collect a packet byte. Returns 0 if the byte was ignored
     * or if there was an error (check with lastError()).
     * 
     * The byte will be ignored if a start byte wasn't collected,
     * or if a end byte was read. In the last case, if there wasn't
     * errors, use available() and read() to read the payload.
     * 
     * @param data      byte to be collected
     * @return size_t   1 if the byte was collected
     */
    size_t write(uint8_t data);

    /**
     * Collect multiple bytes. Calls write() for every byte.
     * 
     * @param data      bytes to be collected
     * @param quantity  number of bytes to collect
     * @return size_t   number of bytes collected
     */
    size_t write(const uint8_t *data, size_t quantity);

    /**
     * Returns number of payload bytes available to be read.
     * Will also return 0 if the packet wasn't processed.
     * 
     * @return size_t
     */
    size_t available();

    /**
     * Read the next available payload byte. At each call,
     * the value returned by available() will be decremented.
     * 
     * @return int  -1 if there are no bytes to be read
     */
    int read();

    /**
     * Resets the unpacking process.
     */
    void reset();

    bool hasError() const { return _last_error != Error::NONE; }
    
    Error lastError() const { return _last_error; }

    /**
     * Returns true if a start byte was read and more packet
     * bytes are expected.
     * 
     */
    bool isPacketOpen() const { return _is_packet_open; }

    /**
     * Returns number of packet bytes read so far.
     * 
     */
    uint16_t totalLength() const { return _total_length; }

    /**
     * Debug. Prints packet data to Serial.
     * 
     */
    #ifdef UNPACKER_DEBUG
    void printToSerial();
    #endif

private:
    const uint8_t _frame_start = 0x02;
    const uint8_t _frame_end = 0x04;

    uint8_t _buffer[UNPACKER_BUFFER_LENGTH];
    uint8_t _index;
    uint8_t _total_length;
    uint8_t _payload_length;
    bool _is_packet_open;
    uint8_t _expected_length;
    uint8_t _expected_crc;

    Error _last_error;
};
#endif // __DATAUNWRAPPER_H__
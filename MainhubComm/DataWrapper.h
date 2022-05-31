#ifndef __DATAWRAPPER_H__
#define __DATAWRAPPER_H__

#define PACKER_BUFFER_LENGTH 128

#define PACKER_DEBUG

#define FRAME_START 0x02;
#define FRAME_END 0x04;

#include <cstring>
#include <stddef.h>
#include <cstdint>
class DataWrapper
{
public:
    DataWrapper();
    
    /**
     * Add a byte to the packet, only if end() was not called yet.
     * 
     * @param data      byte to be added
     * @return size_t   1 if the byte was added
     */
    size_t write(uint8_t data);

    /**
     * Add a number of bytes to the packet. The number of bytes added
     * may be different from quantity if the buffer becomes full.
     * 
     * @param data      byte array to be added
     * @param quantity  number of bytes to add
     * @return size_t   number of bytes added
     */
    size_t write(const uint8_t *data, size_t quantity);

    inline size_t write(const char * s) { return write((uint8_t*) s, strlen(s)); }
    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }

    /**
     * Returns packet length so far
     * 
     * @return size_t 
     */
    size_t packetLength() const { return _is_packet_open ? (_total_length + 2) : _total_length; }

    /**
     * Closes the packet. After that, use avaiable() and read()
     * to get the packet bytes.
     * 
     */
    void end();

    /**
     * Returns how many packet bytes are available to be read.
     * 
     * @return size_t
     */
    size_t available();

    /**
     * Read the next available packet byte. At each call,
     * the value returned by available() will be decremented.
     * 
     * @return int  -1 if there are no bytes to be read
     */
    int read();

    /**
     * Resets the packing process.
     * 
     */
    void reset();

    /**
     * Debug. Prints packet data to Serial.
     * 
     */
    #ifdef PACKER_DEBUG
    void printToSerial();
    #endif

private:
    uint8_t _buffer[PACKER_BUFFER_LENGTH];
    uint8_t _index;
    uint8_t _total_length;
    bool _is_packet_open;
};

#endif // __DATAWRAPPER_H__
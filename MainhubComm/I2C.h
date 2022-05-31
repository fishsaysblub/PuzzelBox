#ifndef __I2C_H__
#define __I2C_H__

#include <unistd.h>        	//Needed for I2C port
#include <fcntl.h>          //Needed for I2C port
#include <sys/ioctl.h>      //Needed for I2C port
#include <linux/i2c-dev.h>  //Needed for I2C port
#include <linux/i2c.h>      //Needed for I2C port

#include <iostream>
#include <iomanip>
#include <string>
#include <cerrno>
#include <cstdint>
#include <cstring>

class I2C
{
	public:
		I2C(std::string filename, const int i2c_addr);
		virtual ~I2C() = default;

		int i2c_read_block(uint8_t reg, uint8_t length, unsigned char* buffer);
		int i2c_write_block(uint8_t reg, uint8_t length, unsigned char* buffer);

	private:
		int file_descriptor;
};


#endif // __I2C_H__
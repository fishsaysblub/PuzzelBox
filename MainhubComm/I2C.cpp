/*************************************************************
 * @file I2C.cpp
 * @author fishsaysblub (lj.vangastel@student.avans.nl)
 * @brief 
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 *************************************************************/

#include "I2C.h"
#include <iostream>

I2C::I2C(std::string filename, const int i2c_addr) : file_descriptor(0)
{
	//----- OPEN THE I2C BUS -----
    int rv;

    if ((file_descriptor = open(filename.c_str(), O_RDWR)) < 0)
    {
        //ERROR HANDLING: you can check errno to see what went wrong
        std::cout << "Failed to open the i2c bus. Error code: " << file_descriptor << std::endl;
    }

    if ((rv = ioctl(file_descriptor, I2C_SLAVE, i2c_addr)) < 0)
    {
        std::cout << "Failed to acquire bus access and/or talk to slave. Error code: " << rv << std::endl;
        //ERROR HANDLING; you can check errno to see what went wrong
        file_descriptor = rv;
    }

	if (file_descriptor < 0)
    {
        std::cerr << "Set UP I2C Bus Error. Exit now!" << std::endl;
    }
}

int I2C::i2c_read_block(uint8_t reg, uint8_t length, unsigned char* buffer)
{
	struct i2c_smbus_ioctl_data ioctl_data;
    union i2c_smbus_data smbus_data;

    int rv; 

    if(length > I2C_SMBUS_BLOCK_MAX) 
    {
        std::cerr << "Requested Length is greater than the maximum specified" << std::endl;
        return -1;
    }

    // First byte is always the size to write and to receive 
    // https://github.com/torvalds/linux/blob/master/drivers/i2c/i2c-core-smbus.c  
    // (See i2c_smbus_xfer_emulated CASE:I2C_SMBUS_I2C_BLOCK_DATA)
    smbus_data.block[0] = length;


    ioctl_data.read_write = I2C_SMBUS_READ;
    ioctl_data.command = reg;
    ioctl_data.size = I2C_SMBUS_I2C_BLOCK_DATA;
    ioctl_data.data = &smbus_data;

    rv = ioctl (file_descriptor, I2C_SMBUS, &ioctl_data);
    if (rv < 0)
    {
        std::cerr << "Accessing I2C Read/Write failed! Error is: " << strerror(errno) << std::endl;
        return rv;
    }

	for(int i = 0; i < length; i++)
	{
		// Skip the first byte, which is the length of the rest of the block.
		buffer[i] = smbus_data.block[i+1];
	}

    return rv;
}

int I2C::i2c_write_block(uint8_t reg, uint8_t length, unsigned char* buffer)
{
	struct i2c_smbus_ioctl_data ioctl_data;
    union i2c_smbus_data smbus_data;


    int rv; 

    if(length > I2C_SMBUS_BLOCK_MAX) 
    {
        std::cerr << "Requested Length is greater than the maximum specified" << std::endl;
        return -1;
    }

    // First byte is always the size to write and to receive 
    // https://github.com/torvalds/linux/blob/master/drivers/i2c/i2c-core-smbus.c  
    // (See i2c_smbus_xfer_emulated CASE:I2C_SMBUS_I2C_BLOCK_DATA)
    smbus_data.block[0] = length;

	for(int i = 0; i < length; i++)
		smbus_data.block[i + 1] = buffer[i];


    ioctl_data.read_write = I2C_SMBUS_WRITE;
    ioctl_data.command = reg;
    ioctl_data.size = I2C_SMBUS_I2C_BLOCK_DATA;
    ioctl_data.data = &smbus_data;

    rv = ioctl (file_descriptor, I2C_SMBUS, &ioctl_data);
    if (rv < 0)
    {
        std::cerr << "Accessing I2C Read/Write failed! Error is: " << strerror(errno) << std::endl;
        return rv;
    }

    return rv;
}

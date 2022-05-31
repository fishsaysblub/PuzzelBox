/*************************************************************
 * @file I2C_Controller.cpp
 * @author fishsaysblub (lj.vangastel@student.avans.nl)
 * @brief 
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 *************************************************************/

#include "I2C_Controller.h"
#include "DataWrapper.h"
#include "Mails.h"

#include <chrono>
#include <thread>


#define BUS_NUM 0x40
#define WAKEUP_PIN 0x200000000 // 2^33 in hex

const std::string i2c_filename = "/dev/i2c-1";

I2C_Controller::I2C_Controller()
{
}


void I2C_Controller::start_mail_transmission(MailEntryType* mail)
{  
    std::map<uint8_t, I2C*>::iterator it = _I2C_devices.find((uint8_t)mail->Dst);
    if(it == _I2C_devices.end())
    {
        std::cout << "Cannot send mail to unknown address [" <<  (int)mail->Dst << "]" <<std::endl;
        return;
    }
    
    DataWrapper w;
    w.write(reinterpret_cast<uint8_t*>(mail), mail->Size);
    w.end();

    w.printToSerial();

    uint8_t packetLength = w.packetLength();
    uint8_t* buffer = reinterpret_cast<uint8_t*>(calloc(packetLength, sizeof(uint8_t)));
    int i = 0;

    while(w.available())
        buffer[i++] = w.read();


    it->second->i2c_write_block(buffer[0], packetLength, &buffer[1]);
    delete(buffer);
}

void I2C_Controller::add_device(uint8_t i2c_address)
{   
    _I2C_devices.insert( std::pair<uint8_t,I2C*>(i2c_address, new I2C(i2c_filename, i2c_address)) );
}

int I2C_Controller::pollDeviceStatus(uint8_t i2c_address)
{
    std::map<uint8_t, I2C*>::iterator it = _I2C_devices.find((uint8_t)i2c_address);
 	uint8_t i2c_data_length = 3;
    int rv;
    unsigned char values[i2c_data_length] = 
	{
		0x04, 0x00, 0x04
	};

    if(it == _I2C_devices.end())
    {
        std::cout << "Cannot write to unknown address [" << std::hex << (int)i2c_address << "]" <<std::endl;
        return -1;
    }

    rv = I2C_Controller::Instance().write_device(0x40, 0x02, i2c_data_length, values);

    if (rv < 0)
    {
        std::cerr << "Writing I2C Bus Error..." << std::endl;
        return -1;
    }

	using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
    sleep_for(milliseconds(250));

    i2c_data_length = 5;
    unsigned char buffer[i2c_data_length + 1] = {0};
	rv = I2C_Controller::Instance().read_device(0x40, 0x22, i2c_data_length, buffer);

    if (rv < 0)
    {
        std::cerr << "Reading I2C Bus Error..." << std::endl;
        return -1;
    }

    std::cout << "Buffer Value: " ;

    for (int i = 0; i < i2c_data_length; i++)
    {
        std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << (int) buffer[i] << " " ;
    }

	return buffer[2];
}

I2C_Controller::~I2C_Controller()
{
    for (auto const& x : _I2C_devices)
        delete(x.second);

    _I2C_devices.clear();
}
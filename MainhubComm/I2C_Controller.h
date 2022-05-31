#ifndef __I2C_CONTROLLER_H__
#define __I2C_CONTROLLER_H__

#include <iostream>
#include <functional>

#include <Mails.h>
#include <map>
#include <I2C.h>
#include <stdint.h>

/**
 * @brief 
 * 
 */
class I2C_Controller final
{
    public:
        static I2C_Controller& Instance()
        {
            static I2C_Controller INSTANCE;
            return INSTANCE;
        }

        /**
         * @brief 
         * 
         * @tparam T 
         * @param Mail 
         */
        template<class T>
        void send_mail(T* Mail);

        void add_device(uint8_t i2c_address);

        inline int read_device(uint8_t i2c_address, uint8_t reg, uint8_t length, unsigned char* buffer) 
        {
            std::cout << "Read from address [" << std::hex << (int)i2c_address << "] length [" << (int)length << "]" << std::endl;

            std::map<uint8_t, I2C*>::iterator it = _I2C_devices.find((uint8_t)i2c_address);
            if(it == _I2C_devices.end())
            {
                std::cout << "Cannot read from unknown address [" << std::hex << (int)i2c_address << "]" <<std::endl;
                return -1;
            }

            return it->second->i2c_read_block(reg, length, buffer);
        }
        int write_device(uint8_t i2c_address, uint8_t reg, uint8_t length, unsigned char* buffer)
        {
            std::cout << "Write to address [" << std::hex << (int)i2c_address << "] length [" << (int)length << "]" << std::endl;
            std::map<uint8_t, I2C*>::iterator it = _I2C_devices.find((uint8_t)i2c_address);
            if(it == _I2C_devices.end())
            {
                std::cout << "Cannot write to unknown address [" << std::hex << (int)i2c_address << "]" <<std::endl;
                return -1;
            }

            return it->second->i2c_write_block(reg, length, buffer);
        }

        int pollDeviceStatus(uint8_t i2c_address);

    private:
        I2C_Controller();
        virtual ~I2C_Controller();
        void find_i2c_devices();

        void start_mail_transmission(MailEntryType* mail);

        std::map<uint8_t, I2C*> _I2C_devices;
};


#include <I2C_Controller.hpp>

#endif // __I2C_CONTROLLER_H__
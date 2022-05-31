#ifndef __I2C_CONTROLLER_H__
#define __I2C_CONTROLLER_H__

#include <iostream>
#include <functional>
#include <stdint.h>

#include <Mails.h>

#define I2C_SDA 21
#define I2C_SCL 22

#define I2C_PI_ADDRESS 0x01
#define I2C_SELF_ADDRESS 0x02

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

        void attach_callback(std::function<void(MailType*)> cb);

    private:
        I2C_Controller();
        virtual ~I2C_Controller();
        void find_i2c_devices();

        void start_mail_transmission(MailEntryType* mail);
};


#include <I2C_Controller.hpp>

#endif // __I2C_CONTROLLER_H__
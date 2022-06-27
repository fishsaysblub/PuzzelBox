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
#include <Arduino.h>
#include "FixedI2C/FixedI2C.h"
#define BUS_NUM 0x41
#define WAKEUP_PIN 0x200000000 // 2^33 in hex

#include "Wire.h"

MailEntryType* CurrentMail = nullptr;
std::function<void(MailType*)> Callback;

TaskHandle_t ReceiveTask;

void receive_data(void*);
void transmit_mail();

void on_data_request()
{
    Serial.print("Master requested data, returning [");
    Serial.print(I2C_Controller::Instance().get_status());
    Serial.print("]\n");
    FixedWire.write(I2C_Controller::Instance().get_status());
}

void on_receive_data(int how_many)
{
    uint8_t* data = reinterpret_cast<uint8_t*>(malloc(how_many * sizeof(uint8_t)));
    int i = 0;

    while(FixedWire.available() > 1)
    {
        data[i] = FixedWire.read();
        i += 1;
    }

    MailEntryType* mail = (MailEntryType*)data;
    Callback(&mail->Mail);
    delete(mail);
}

I2C_Controller::I2C_Controller()
{
    if (!FixedWire.begin(I2C_SDA, I2C_SCL, BUS_NUM)) {
        Serial.write("I2C slave init failed\n");
    }

    Serial.print("Created I2C on SDA[");
    Serial.print(I2C_SDA);
    Serial.print("] and SCL[");
    Serial.print(I2C_SCL);
    Serial.print("] with bus number[");
    Serial.print(BUS_NUM);
    Serial.print("]\n");

    FixedWire.onRequest(on_data_request);
    FixedWire.onReceive(on_receive_data);
}


void I2C_Controller::start_mail_transmission(MailEntryType* mail)
{  
    DataWrapper w;
    w.write(reinterpret_cast<uint8_t*>(mail), mail->Size);
    w.end();

    w.printToSerial();

    uint16_t packetLength = w.packetLength();
    uint8_t* buffer = reinterpret_cast<uint8_t*>(calloc(packetLength, sizeof(uint8_t)));
    int i = 0;

    while(w.available())
        buffer[i++] = w.read();

    FixedWire.write(buffer, uint16_t(packetLength));
    delete(buffer);
}

/*************************************************************
 * @brief Sets the callback for received mails.
 * 
 * @param cb callback to use.
**************************************************************/
void I2C_Controller::attach_callback(std::function<void(MailType*)> cb)
{
    Callback = cb;
}

I2C_Controller::~I2C_Controller()
{

}
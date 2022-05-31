/*************************************************************
 * @file main.cpp
 * @author fishsaysblub (lj.vangastel@student.avans.nl)
 * @brief 
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
**************************************************************/

#include <Arduino.h>
#include <Mails.h>
#include <I2C_Controller.h>
#include <esp32-hal-i2c.h>
#include "FixedI2C/FixedI2C.h"

void IReceivedData(MailType* whatyaget);

void setup() 
{
	// put your setup code here, to run once:
	MailP1Type* test = AllocateMail<MailP1Type>(I2C_SELF_ADDRESS, I2C_PI_ADDRESS, sizeof(MailP1Type) /* + sizeof(data_array)*/);
	test->Primitive = GAME_START;
	test->status = SUCCESS;
	test->P1 = 0xFF;

	// put your setup code here, to run once:
	/*uint8_t data_array[10];*/

	/*DataMailType* test2 = AllocateMail<DataMailType>(I2C_SELF_ADDRESS, I2C_PI_ADDRESS, sizeof(DataMailType) + sizeof(data_array));
	test2->Primitive = GAME_ERROR;
	test2->status = SUCCESS;
	test2->length = sizeof(data_array);
	memcpy(test2->Data, data_array, sizeof(data_array));
	*/

	Serial.begin(9600);
	Serial.println("\nBefore setup!");
	I2C_Controller::Instance().attach_callback(IReceivedData);
	Serial.println("Started!");

	I2C_Controller::Instance().send_mail(test);

	Serial.println("====================== REQUEST =================");
	/// w4@0x40	0x02 	0x04 		0x00 		0x04
	//			Start - length - 	No crc -  	End
	Serial.println("0x02 0x04 0x00 0x04");
	Serial.println("================================================");
}

void test(MailType* m)
{
	Serial.write("got mail\n");
}

void IReceivedData(MailType* whatyaget)
{
  	Serial.print("Mail Gotten, primitive[");
    Serial.print(whatyaget->Primitive);
    Serial.print("]\n");

	if(whatyaget->Primitive == GAME_START)
	{
		MailP1Type* whatigot = reinterpret_cast<MailP1Type*>(whatyaget);
		if(whatigot->status != SUCCESS)
			return; 

		whatigot->P1;		// 0xFF
		whatigot->status; 	// SUCCESS

		Serial.print("p1[");
		Serial.print(whatigot->P1);
		Serial.print("]\n");

		Serial.print("status[");
		Serial.print(whatigot->status);
		Serial.print("]\n");
	}

	if(whatyaget->Primitive == GAME_ERROR)
	{
		DataMailType* whatigot = reinterpret_cast<DataMailType*>(whatyaget);
		
		if(whatigot->status != SUCCESS)
			return; 

		for (size_t i = 0; i < whatigot->length; i++)
		{
			whatigot->Data[i];
		}
	}
}

void loop() 
{
	// put your main code here, to run repeatedly:
	FixedWire.update();
}


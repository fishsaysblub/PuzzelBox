#include "../include/GpioManager.h"
#include <wiringPi.h>
#include "iostream"

GpioManager::GpioManager()
{
	wiringPiSetup();

	pinMode(LDR_PIN, INPUT);

	pinMode(CLK_PIN, INPUT);
	pinMode(DATA_PIN, INPUT);
	pinMode(INTERRUPT_PIN, INPUT);

	pinMode(LED_STRIP_R, OUTPUT);
	pinMode(LED_STRIP_B, OUTPUT);
	pinMode(LED_STRIP_G, OUTPUT);
}

bool GpioManager::read_ldr()
{
	return (bool)digitalRead(LDR_PIN);
}

void GpioManager::set_ledstrip( bool r, bool b, bool g )
{
	digitalWrite(LED_STRIP_R, r);
	digitalWrite(LED_STRIP_B, b);
	digitalWrite(LED_STRIP_G, g);
}

void GpioManager::blink_leds()
{
	this->set_ledstrip(true, false, false);
	std::cout << "Red ";
	delay(1000);
	this->set_ledstrip(false, true, false);
	std::cout << "Green ";
	delay(1000);
	this->set_ledstrip(false, false, true);
	std::cout << "BLue\n";
	delay(1000);
	this->set_ledstrip(false, false, false);
}
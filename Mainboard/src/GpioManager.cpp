#include "../include/GpioManager.h"
#include <wiringPi.h>

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
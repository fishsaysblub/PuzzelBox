#include <Arduino.h>
#include "GpioManager.h"

GpioManager::GpioManager():
	display(CLOCK_PIN_DISPLAY, DATA_PIN_DISPLAY)
{
	for(int i = 0; i < NUMBER_OF_POTENTIOMETERS; i++)
	{
		pinMode(POTENTIOMETERS[i], INPUT);
	}

	pinMode(BUZZER_PIN		 , OUTPUT);
	pinMode(DATA_PIN_BUTTONS , OUTPUT);
	pinMode(CLOCK_PIN_BUTTONS, OUTPUT);
	pinMode(LATCH_PIN_BUTTONS, OUTPUT);

	display.setBrightness(MAX_BRIGHTNESS);
}

void GpioManager::set_display_value(int value)
{
	display.showNumberDec(value, false);
}

TM1637Display GpioManager::get_display_instance()
{
	return display;
}


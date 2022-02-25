#include <Arduino.h>
#include "GpioManager.h"

GpioManager::GpioManager():
	display(CLK_PIN, DATA_PIN)
{
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


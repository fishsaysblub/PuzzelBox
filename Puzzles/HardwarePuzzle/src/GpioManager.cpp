#include <Arduino.h>
#include "GpioManager.h"

GpioManager::GpioManager():
	display(CLOCK_PIN_DISPLAY, DATA_PIN_DISPLAY)
{
	for(int i = 0; i < NUMBER_OF_POTENTIOMETERS; i++)
	{
		pinMode(POTENTIOMETERS[i], INPUT);
	}

	pinMode(RESULT_LED		 , OUTPUT);
	pinMode(BUZZER_PIN		 , OUTPUT);
	pinMode(DATA_PIN_BUTTONS , INPUT );
	pinMode(CLOCK_PIN_BUTTONS, OUTPUT);
	pinMode(LATCH_PIN_BUTTONS, OUTPUT);
	pinMode(CLKIN_PIN_BUTTONS, OUTPUT);

	display.setBrightness(MAX_BRIGHTNESS);
}

void GpioManager::set_display_value(int value)
{
	display.showNumberDec(value, true);
}

void GpioManager::set_buzzer_pin(int freq)
{
	if (!_buzzer_pin_initialized)
	{	
		ledcSetup(0, 440, 8);
		ledcAttachPin(BUZZER_PIN, 0);
		ledcWrite(0, 127);
		_buzzer_pin_initialized = true;
	}

	ledcWriteTone(0, freq);
}

void GpioManager::set_result_led(int value)
{
	digitalWrite(RESULT_LED, value);
}

TM1637Display GpioManager::get_display_instance()
{
	return display;
}


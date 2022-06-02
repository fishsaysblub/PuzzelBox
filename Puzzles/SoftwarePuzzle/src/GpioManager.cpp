#include <Arduino.h>
#include "GpioManager.h"

GpioManager::GpioManager()
{
	for(int i = 0; i < PIN_COUNT_IO; i++)
	{
		pinMode(INPUTS[i], INPUT);
		pinMode(OUTPUTS[i], OUTPUT);
	}

	pinMode(OE_PIN, OUTPUT);
	pinMode(MR_PIN, OUTPUT);

	pinMode(CLK_PIN, OUTPUT);
	pinMode(DATA_PIN, OUTPUT);
	pinMode(LATCH_PIN, OUTPUT);
}

void GpioManager::initialize_ledController()
{
	digitalWrite(MR_PIN, HIGH);
	digitalWrite(OE_PIN, LOW);
}

void GpioManager::set_clk_pin(bool value)
{
	digitalWrite(CLK_PIN, value);
}

void GpioManager::set_data_pin(bool value)
{
	digitalWrite(DATA_PIN, value);
}

void GpioManager::set_latch_pin(bool value)
{
	digitalWrite(LATCH_PIN, value);
}

int GpioManager::get_input_pin_value(int index)
{
	if (index < PIN_COUNT_IO)
	{
		return digitalRead(INPUTS[index]);
	}
}

void GpioManager::set_output_pin(int index, bool value)
{
	if (index < PIN_COUNT_IO)
	{
		digitalWrite(OUTPUTS[index], value);
	}
}

void GpioManager::render_leds(uint16_t value)
{
	LedValues ledValues;
	ledValues.value = value;

	digitalWrite(LATCH_PIN, LOW);

	shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, ledValues.byte_one);
	shiftOut(DATA_PIN, CLK_PIN, MSBFIRST, ledValues.byte_two);

	digitalWrite(LATCH_PIN, HIGH);
}
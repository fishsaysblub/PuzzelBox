#include <Arduino.h>
#include "GpioManager.h"

GpioManager::GpioManager():
	_number_of_pins(6),
	_data_pin(0),
	_clock_pin(0),
	_latch_pin((0)),
	_input_pins{0,1,2,3,4,5},
	_output_pins{0,1,2,3,4,5}
{
}

GpioManager::~GpioManager()
{

}

void GpioManager::start_manager()
{
	Serial.begin(9600);
	Serial.print("\n\n");
}

void GpioManager::setup_pins()
{
	for(int i = 0; i < _number_of_pins; i++)
	{
		pinMode(_input_pins[i], INPUT);
		pinMode(_output_pins[i], OUTPUT);
	}

	pinMode(_data_pin, OUTPUT);
	pinMode(_clock_pin, OUTPUT);
	pinMode(_latch_pin, OUTPUT);
}
#include <Arduino.h>
#include "GpioManager.h"

GpioManager::GpioManager():
	_data_pin(27),
	_clock_pin(14),
	_latch_pin((13)),
	_input_pins{9,35,34,36,39,25},
	_output_pins{21,22,19,23,18,5}
{
	for(int i = 0; i < PIN_COUNT_IO; i++)
	{
		pinMode(_input_pins[i], INPUT);
		pinMode(_output_pins[i], OUTPUT);
	}

	pinMode(_data_pin, OUTPUT);
	pinMode(_clock_pin, OUTPUT);
	pinMode(_latch_pin, OUTPUT);
}

int GpioManager::get_data_pin()
{
	return _data_pin;
}

int GpioManager::get_clock_pin()
{
	return _clock_pin;
}

int GpioManager::get_latch_pin()
{
	return _latch_pin;
}

int GpioManager::get_input_pin( int index )
{
	if ( index < PIN_COUNT_IO )
	{
		return _input_pins[index];
	}
	else
	{
		return -1;
	}
}

int GpioManager::get_output_pin( int index )
{
	if ( index < PIN_COUNT_IO )
	{
		return _output_pins[index];
	}
	else
	{
		return -1;
	}
}

#include <string>
#include <sstream>
#include <Arduino.h>
#include "GpioManager.h"
#include "StateMachine.h"
#include "States/RunningState.h"

RunningState::RunningState() : 
	_check_list{},
	_output_values{},
	_correct_output{}
{
}

RunningState::~RunningState()
{
}

void RunningState::on_enter()
{
	Serial.println("Enter Running");

	int correct[6] = {4, 3, 2, 1, 0, 5};
	set_correct_output(correct);

	RunningState::on_stay();
}

void RunningState::on_stay()
{
	while (!check_completed())
	{
		get_user_input();
	}

	render_leds(21845);
	StateMachine::instance().change_state(COMPLETED);
}

void RunningState::set_correct_output(int arr[6])
{
	for (int i = 0; i < GpioManager::instance().number_of_pins; i++)
	{
		_correct_output[i] = arr[i];
	}
}

void RunningState::get_user_input()
{
	for (int i = 0; i < GpioManager::instance().number_of_pins; i++)
	{
		digitalWrite(GpioManager::instance().get_output_pin(i), HIGH);

		bool pinIsConnected = false;

		for (int j = 0; j < GpioManager::instance().number_of_pins; j++)
		{
			if (digitalRead(GpioManager::instance().get_input_pin(j)))
			{
				pinIsConnected = true;
				_output_values[i] = j;
				break;
			}
		}

		if (!pinIsConnected)
		{
			_output_values[i] = -1;
		}

		digitalWrite(GpioManager::instance().get_output_pin(i), LOW);
	}
}

bool RunningState::check_completed()
{
	for (int i = 0; i < GpioManager::instance().number_of_pins; i++)
	{
		if (_output_values[i] != _correct_output[i])
		{
			return false;
		}
	}

	return true;
}

void RunningState::render_leds(uint16_t value)
{
	byte byteOne = (value >> 0) & 0xFF;
	byte byteTwo = (value >> 8) & 0xFF;

	digitalWrite(GpioManager::instance().get_latch_pin(), LOW);

	shiftOut(GpioManager::instance().get_data_pin(),
			 GpioManager::instance().get_clock_pin(), MSBFIRST, byteOne);
	shiftOut(GpioManager::instance().get_data_pin(),
			 GpioManager::instance().get_clock_pin(), MSBFIRST, byteTwo);

	digitalWrite(GpioManager::instance().get_latch_pin(), HIGH);
}

void RunningState::on_exit()
{
	Serial.println("Exit Running\n");
}

void RunningState::printOutputValues()
{
	std::string print = "Output values: \n";

	for (int i = 0; i < 6; i++)
	{
		print += "IO" + utils.intToString(i) + " = " + utils.intToString(_output_values[i]) + "\n";
	}

	Serial.println(print.c_str());
}

void RunningState::test_leds_and_shiftregisters()
{
	render_leds(21845);
	delay(400);
	render_leds(43690);
	delay(400);
}
#include <string>
#include <Arduino.h>
#include "GpioManager.h"
#include "StateMachine.h"
#include "States/RunningState.h"

RunningState::RunningState() : 
	_check_list{},
	_input_values{},
	_correct_output{}
{
}

RunningState::~RunningState()
{
}

void RunningState::on_enter()
{
	Serial.println("Enter Running");

	int correct[PIN_COUNT_IO] = {0, 1, 2, 3, 4, 5};
	set_correct_output(correct);
}

void RunningState::on_stay()
{
	get_user_input();
	puzzle_finished();
	//print_output_values();
}

void RunningState::set_correct_output(int *ouput_array)
{
	for (int i = 0; i < PIN_COUNT_IO; i++)
	{
		_correct_output[i] = ouput_array[i];
	}
}

void RunningState::get_user_input()
{
	for (int i = 0; i < PIN_COUNT_IO; i++)
	{
		GpioManager::instance().set_output_pin(i, HIGH);

		bool pinIsConnected = false;

		for (int j = 0; j < PIN_COUNT_IO; j++)
		{
			if (GpioManager::instance().get_input_pin_value(j))
			{
				pinIsConnected = true;
				_input_values[i] = j;
				break;
			}
		}

		if (!pinIsConnected)
		{
			_input_values[i] = -1;
		}

		GpioManager::instance().set_output_pin(i, LOW);
	}
}

void RunningState::puzzle_finished()
{
	for (int i = 0; i < PIN_COUNT_IO; i++)
	{
		if (_input_values[i] != _correct_output[i])
		{
			return;
		}
	}

	Serial.println("Puzzle Completed");
	
	/*
	while( 1 )
	{
		test_leds_and_shiftregisters();
	}
	*/
	GpioManager::instance().render_leds(21845); // TODO: Add real dismantle codes
	StateMachine::instance().change_state(COMPLETED);
}

void RunningState::on_exit()
{
	Serial.println("Exit Running\n");
}

void RunningState::print_output_values()
{
	std::string print = "Output values: \n";

	for (int i = 0; i < 6; i++)
	{
		print += "IO" + _utils.int_to_string(i) + " = " + _utils.int_to_string(_input_values[i]) + "\n";
	}

	Serial.println(print.c_str());
}

void RunningState::test_leds_and_shiftregisters()
{
	GpioManager::instance().render_leds(21845);
	delay(400);
	GpioManager::instance().render_leds(43690);
	delay(400);
}
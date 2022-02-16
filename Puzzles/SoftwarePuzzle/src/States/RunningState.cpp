#include <Arduino.h>
#include "StateMachine.h"
#include "States/RunningState.h"

RunningState::RunningState():
	_check_list({}),
	_output_values({})
{
}

RunningState::~RunningState()
{
}

void RunningState::on_enter()
{
	Serial.println("Enter Running");
	StateMachine::instance().change_state(COMPLETED);
}

void RunningState::get_user_input()
{
	for(int i = 0; i < number_of_output_pins; i++) 
	{
		digitalWrite(StateMachine::instance().get_output_pin(i), HIGH);

		for(int j = 0; j < number_of_input_pins; j++)
		{
			_output_values[j] = digitalRead(StateMachine::instance().get_input_pin(j));
		}

		if(_output_values[i])
		{
			_check_list[i] = true;
		}
		else
		{
			_check_list[i] = false;
		}

		digitalWrite(StateMachine::instance().get_output_pin(i), LOW);
	}
}

bool RunningState::check_completed()
{
	for(int i = 0; i < number_of_input_pins; i++)
	{
		if(!_check_list[i])
		{
			return false;
		}
	}

	return true;
}

void RunningState::render_leds( uint16_t value )
{
	byte byteOne = (value >> 0) & 0xFF;
	byte byteTwo = (value >> 8) & 0xFF;

	delay(1);
	digitalWrite(StateMachine::instance().get_latch_pin(), LOW);

	shiftOut(StateMachine::instance().get_data_pin(), 
		StateMachine::instance().get_clock_pin(), LSBFIRST, byteTwo);
	shiftOut(StateMachine::instance().get_data_pin(), 
		StateMachine::instance().get_clock_pin(), LSBFIRST, byteOne);
		
	delay(1);
	digitalWrite(StateMachine::instance().get_latch_pin(), HIGH);
}

void RunningState::on_stay()
{
	while( check_completed() )
	{
		get_user_input();
	}

	render_leds(26133);
}

void RunningState::on_exit()
{
	Serial.println("Exit Running\n");
}
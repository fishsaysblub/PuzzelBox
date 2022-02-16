#include "States/InitializeState.h"
#include "StateMachine.h"
#include <Arduino.h>

InitializeState::InitializeState()
{
}

InitializeState::~InitializeState()
{
}

void InitializeState::on_enter()
{
	Serial.println("Enter Init");
	InitializeState::on_stay();
}

void InitializeState::on_stay()
{
	for(int i = 0; i < number_of_input_pins; i++)
	{
		pinMode(StateMachine::instance()._input_pins[i], INPUT);
		pinMode(StateMachine::instance()._output_pins[i], OUTPUT);
	}

	pinMode(StateMachine::instance().data_pin, OUTPUT);
	pinMode(StateMachine::instance().clock_pin, OUTPUT);
	pinMode(StateMachine::instance().latch_pin, OUTPUT);

	StateMachine::instance().change_state(HYBERNATE);
}

void InitializeState::on_exit()
{
	Serial.println("Leave Init\n");
}

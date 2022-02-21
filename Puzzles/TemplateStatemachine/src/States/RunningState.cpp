#include <Arduino.h>
#include "GpioManager.h"
#include "StateMachine.h"
#include "States/RunningState.h"

RunningState::RunningState()
{
}

RunningState::~RunningState()
{
}

void RunningState::on_enter()
{

}

void RunningState::on_stay()
{
	while (!check_completed())
	{
		get_user_input();
	}

	Serial.println("Puzzle Completed");
	StateMachine::instance().change_state(COMPLETED);
}

void RunningState::get_user_input()
{
}

bool RunningState::check_completed()
{
	return true;
}

void RunningState::on_exit()
{
	Serial.println("Exit Running\n");
}
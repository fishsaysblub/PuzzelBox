#include <string>
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
	Serial.println("Enter Running");
}

void RunningState::on_stay()
{
	get_user_input();
	puzzle_finished();
}


void RunningState::get_user_input()
{

}

void RunningState::puzzle_finished()
{
	
}

void RunningState::on_exit()
{
	Serial.println("Exit Running\n");
}
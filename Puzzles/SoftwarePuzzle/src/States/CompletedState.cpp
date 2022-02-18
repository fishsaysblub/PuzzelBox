#include <Arduino.h>
#include "StateMachine.h"
#include "States/CompletedState.h"

CompletedState::CompletedState()
{
}

CompletedState::~CompletedState()
{
}

void CompletedState::on_enter()
{
	Serial.println("Enter Completed");
	delay(1000);
	StateMachine::instance().change_state(HYBERNATE);
}

void CompletedState::on_exit()
{
	Serial.println("Leave Completed\n");
}
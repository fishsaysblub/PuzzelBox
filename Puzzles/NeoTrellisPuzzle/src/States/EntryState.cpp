#include <Arduino.h>
#include "StateMachine.h"
#include "States/EntryState.h"

EntryState::EntryState()
{
}

EntryState::~EntryState()
{
}

void EntryState::on_enter()
{
	Serial.println("Enter Entry");
}

void EntryState::on_stay()
{
	StateMachine::instance().change_state(RUNNING);
}

void EntryState::on_exit()
{
	Serial.println("Leave Entry\n");
}
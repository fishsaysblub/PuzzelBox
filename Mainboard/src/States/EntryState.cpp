#include "../../include/States/EntryState.h"
#include "../../include/StateMachine.h"
#include <stdio.h>

EntryState::EntryState()
{
}

EntryState::~EntryState()
{
}

void EntryState::on_enter()
{
	printf("Enter Entry\n");
}

void EntryState::on_stay()
{
	StateMachine::instance().change_state(RUNNING);
}

void EntryState::on_exit()
{
	printf("Leave Entry\n\n");
}
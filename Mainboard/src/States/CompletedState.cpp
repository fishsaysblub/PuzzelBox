#include "../../include/States/CompletedState.h"
#include "../../include/StateMachine.h"
#include <stdio.h>

CompletedState::CompletedState()
{
}

CompletedState::~CompletedState()
{
}

void CompletedState::on_enter()
{
	printf("Enter Completed\n");
}

void CompletedState::on_stay()
{
	StateMachine::instance().change_state(HYBERNATE);
}

void CompletedState::on_exit()
{
	printf("Leave Completed\n\n");
}
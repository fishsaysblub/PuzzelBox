#include "../../include/States/InitializeState.h"
#include "../../include/StateMachine.h"
#include <stdio.h>

InitializeState::InitializeState()
{
}

InitializeState::~InitializeState()
{
}

void InitializeState::on_enter()
{
	printf("Enter Init\n");
}

void InitializeState::on_stay()
{
	StateMachine::instance().change_state(CHECK);
}

void InitializeState::on_exit()
{
	printf("Leave Init\n\n");
}

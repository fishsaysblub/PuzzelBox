#include "../../include/States/CheckState.h"
#include "../../include/StateMachine.h"
#include <stdio.h>

CheckState::CheckState()
{

}

CheckState::~CheckState()
{

}

void CheckState::on_enter()
{
	printf("Enter Check\n");
}

void CheckState::on_stay()
{
	StateMachine::instance().change_state(RUNNING);
}

void CheckState::on_exit()
{
	printf("Leave Check\n\n");
}
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
	if (check_if_puzzles_are_ready())
	{
		StateMachine::instance().change_state(RUNNING);
	}
}

void CheckState::on_exit()
{
	printf("Leave Check\n\n");
}

bool CheckState::check_if_puzzles_are_ready()
{
	return true; //TODO: Add a callback which sets variable if puzzle is ready
}
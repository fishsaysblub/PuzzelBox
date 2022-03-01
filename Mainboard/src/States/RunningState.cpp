#include "../../include/States/RunningState.h"
#include "../../include/StateMachine.h"
#include <stdio.h>
#include <string>

RunningState::RunningState()
{
}

RunningState::~RunningState()
{
}

void RunningState::on_enter()
{
	printf("Enter Running\n");
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
	StateMachine::instance().change_state(COMPLETED);
}

void RunningState::on_exit()
{
	printf("Exit Running\n\n");
}
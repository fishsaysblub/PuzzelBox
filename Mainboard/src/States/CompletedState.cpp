#include "../../include/States/CompletedState.h"
#include "../../include/StateMachine.h"
#include <unistd.h>
#include <stdio.h>

CompletedState::CompletedState()
{
}

CompletedState::~CompletedState()
{
}

void CompletedState::on_enter()
{
	printf("Enter Completed\n\n");
}

void CompletedState::on_stay()
{
	while(1)
	{
		printf("All puzzles are completed.\n");
		
		unsigned int microsecond = 1000000;
		usleep(3 * microsecond);
	}
}

void CompletedState::on_exit()
{
	printf("\nLeave Completed\n\n");
}
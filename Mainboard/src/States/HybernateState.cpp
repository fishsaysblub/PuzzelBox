#include "../../include/States/HybernateState.h"
#include "../../include/StateMachine.h"
#include <unistd.h>
#include <stdio.h>

HybernateState::HybernateState()
{
}

HybernateState::~HybernateState()
{
}

void HybernateState::on_enter()
{
	printf("Enter Hybernate\n");
}

void HybernateState::on_stay()
{
	printf("Hybernating...\n");

	unsigned int microsecond = 1000000;
	usleep(3 * microsecond); //sleeps for 3 second //TODO: Add real esp sleep function
	
	on_awake();
}

void HybernateState::on_exit()
{
	printf("Leave Hybernate\n\n");
}

void HybernateState::on_awake()
{
	EState beforeHybernationState = StateMachine::instance().get_previous_state();

	if (beforeHybernationState == INITIALIZE)
	{
		StateMachine::instance().change_state(ENTRY);
	}
	else if (beforeHybernationState == COMPLETED)
	{
		StateMachine::instance().change_state(COMPLETED);
	}
	else
	{
		printf("Error: Did not find state after Hybernation.\n");
	}
}
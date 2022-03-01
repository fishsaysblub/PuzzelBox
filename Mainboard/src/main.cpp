#include "../include/StateMachine.h"

int main()
{
	// Start state machine
	StateMachine::instance().start_engine();

	while(1)
	{
		StateMachine::instance().update();
	}

	return 0;
}
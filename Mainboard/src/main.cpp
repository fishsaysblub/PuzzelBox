#include <wiringPi.h>
#include <iostream>
#include "../include/StateMachine.h"

void testGpio()
{
	wiringPiSetup();
	pinMode(25, OUTPUT);

	int a = -1;

	while(1)
	{
		if ( a == -1 )
		{
			digitalWrite(25, 0);
		}
		else
		{
			digitalWrite(25, 1);
		}

		a *= -1;

		delay(500);
	}
}

int main()
{
	testGpio();

	// Start state machine
	StateMachine::instance().start_engine();

	while(1)
	{
		StateMachine::instance().update();
	}

	return 0;
}
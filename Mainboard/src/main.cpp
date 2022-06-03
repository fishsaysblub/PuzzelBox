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



/* Testing */

	// #include "wiringPi.h"
	// #include <softPwm.h>
	// #include <stdio.h>

	// #define G 27//16
	// #define R 28//20
	// #define B 29//21

	/*wiringPiSetup();

	pinMode( R, OUTPUT );
	pinMode( G, OUTPUT );
	pinMode( B, OUTPUT );
	
	softPwmCreate( R, 10, 255 );
	softPwmCreate( G, 10, 255 );
	softPwmCreate( B, 10, 255 );

	while( 1 )
	{
		//156, 11, 144

		for (int i = 0; i < 100; i++)
		{
			softPwmCreate( R, i, 100 );
			delay( 25 );
		}
		
		for (int i = 0; i < 100; i++)
		{
			softPwmCreate( G, i, 100 );
			delay( 25 );
		}

		for (int i = 0; i < 100; i++)
		{
			softPwmCreate( B, i, 100 );
			delay( 25 );
		}

		// digitalWrite( G, HIGH );
		// delay(300);
		// digitalWrite( R, LOW );
		// delay(100);

		// digitalWrite( G, HIGH );
		// delay(300);
		// digitalWrite( G, LOW );

		// digitalWrite( B, HIGH );
		// delay(300);
		// digitalWrite( B, LOW );
	}*/
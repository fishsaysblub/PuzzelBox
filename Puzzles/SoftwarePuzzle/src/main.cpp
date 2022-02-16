#include <Arduino.h>
#include <utility>
#include <Arduino.h>
#include "StateMachine.h"

void setup()
{
	Serial.begin(9600);
	Serial.print("\n\n");

	// Start state machine
	StateMachine::instance().start_engine();
}

void loop()
{
	delay(1000);
	Serial.println("Left statemachine");
}
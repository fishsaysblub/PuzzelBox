#include <Arduino.h>
#include <utility>
#include <Arduino.h>
#include "StateMachine.h"

void setup()
{
	// Start state machine
	StateMachine::instance().start_engine();
}

void loop()
{
	Serial.println("Left statemachine");
	delay(1000);
}
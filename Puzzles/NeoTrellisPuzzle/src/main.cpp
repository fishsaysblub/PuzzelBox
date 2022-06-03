#include <utility>
#include <Arduino.h>
#include "StateMachine.h"

void setup()
{
	Serial.begin(115200);
	Serial.print("\n\n");
	Serial.println("Swiggity Swooty");
	// Start state machine
	StateMachine::instance().start_engine();
}

void loop()
{
	StateMachine::instance().update();
}
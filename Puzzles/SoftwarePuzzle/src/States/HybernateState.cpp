#include <Arduino.h>
#include "StateMachine.h"
#include "States/HybernateState.h"

HybernateState::HybernateState()
{
}

HybernateState::~HybernateState()
{
}

void HybernateState::on_enter()
{
	Serial.println("Enter Hybernate");
}

void HybernateState::on_stay()
{
	Serial.println("Hybernating...");
	delay(1000); //TODO: Add real esp sleep function
	on_awake();
}

void HybernateState::on_exit()
{
	Serial.println("Leave Hybernate\n");
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
		Serial.println("Error: Did not find state after Hybernation.");
	}
}
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
	hybernate();
}

void HybernateState::on_exit()
{
	Serial.println("Leave Hybernate\n");
}

void HybernateState::hybernate()
{
	Serial.println("Hybernating...");
	delay(5000);
	on_awake();
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
	else if (beforeHybernationState == HYBERNATE)
	{
		Serial.println("Found hybernate");
	}
	else
	{
		Serial.println("No previous state found.");
	}
}
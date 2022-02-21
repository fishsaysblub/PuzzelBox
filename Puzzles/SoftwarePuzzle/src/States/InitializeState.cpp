#include "States/InitializeState.h"
#include "StateMachine.h"
#include "GpioManager.h"
#include <Arduino.h>

InitializeState::InitializeState()
{
}

InitializeState::~InitializeState()
{
}

void InitializeState::on_enter()
{
	Serial.println("Enter Init");

	// Start GPIO manager
	GpioManager::instance().start_manager();
}

void InitializeState::on_stay()
{
	GpioManager::instance().setup_pins();
	StateMachine::instance().change_state(HYBERNATE);
}

void InitializeState::on_exit()
{
	Serial.println("Leave Init\n");
}

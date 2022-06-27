#include "States/InitializeState.h"
#include "States/CompletedState.h"
#include "States/HybernateState.h"
#include "States/RunningState.h"
#include "States/EntryState.h"
#include "StateMachine.h"
#include "State.h"
#include <Arduino.h>


#include "FixedI2C/FixedI2C.h"
#include "I2C_Controller.h"

void IReceivedData(MailType* whatyaget)
{
	Serial.print("Mail Gotten, primitive[");
    Serial.print(whatyaget->Primitive);
    Serial.print("]\n");

	if(whatyaget->Primitive == GAME_START)
	{
		MailP1Type* whatigot = reinterpret_cast<MailP1Type*>(whatyaget);
		if(whatigot->status != SUCCESS)
			return; 

		whatigot->P1;		// 0xFF
		whatigot->status; 	// SUCCESS

		Serial.print("p1[");
		Serial.print(whatigot->P1);
		Serial.print("]\n");

		Serial.print("status[");
		Serial.print(whatigot->status);
		Serial.print("]\n");

		if(StateMachine::instance().get_current_state() != RUNNING)
			StateMachine::instance().change_state(ENTRY);
	}

	if(whatyaget->Primitive == GAME_ERROR)
	{
		DataMailType* whatigot = reinterpret_cast<DataMailType*>(whatyaget);
		
		if(whatigot->status != SUCCESS)
			return; 

		for (size_t i = 0; i < whatigot->length; i++)
		{
			whatigot->Data[i];
		}
	}
}

StateMachine::StateMachine() : 
	_previous_state(INVALID),
	_all_states(
	{
	   	{INITIALIZE, new InitializeState},
	 	{HYBERNATE, new HybernateState},
		{ENTRY, new EntryState},
		{RUNNING, new RunningState},
		{COMPLETED, new CompletedState}
	}),
	_current_state({INVALID, nullptr})
{
	I2C_Controller::Instance().attach_callback(IReceivedData);
	I2C_Controller::Instance().set_status(_current_state.first);
}

StateMachine::~StateMachine()
{
	delete _all_states[INITIALIZE];
	delete _all_states[HYBERNATE];
	delete _all_states[ENTRY];
	delete _all_states[RUNNING];
	delete _all_states[COMPLETED];
}

void StateMachine::start_engine()
{
	Serial.println("Start engine\n");
	change_state(INITIALIZE);
}

void StateMachine::change_state(EState eState)
{
	if (_current_state.first != INVALID)
	{
		_current_state.second->on_exit();
		_previous_state = _current_state.first;
	}

	_current_state.first = eState;
	_current_state.second = _all_states[eState];
	
	I2C_Controller::Instance().set_status(_current_state.first);

	_current_state.second->on_enter();
}

void StateMachine::update()
{
	FixedWire.update();
	if (_current_state.first != INVALID)
	{
		_current_state.second->on_stay();
	}
}

EState StateMachine::get_current_state()
{
	return _current_state.first;
}

EState StateMachine::get_previous_state()
{
	return _previous_state;
}

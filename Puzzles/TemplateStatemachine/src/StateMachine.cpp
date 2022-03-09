#include "States/InitializeState.h"
#include "States/CompletedState.h"
#include "States/HybernateState.h"
#include "States/RunningState.h"
#include "States/EntryState.h"
#include "StateMachine.h"
#include "State.h"
#include <Arduino.h>

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

	_current_state.second->on_enter();
}

void StateMachine::update()
{
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

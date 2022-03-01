#include "../include/States/InitializeState.h"
#include "../include/States/CompletedState.h"
#include "../include/States/HybernateState.h"
#include "../include/States/RunningState.h"
#include "../include/States/EntryState.h"
#include "../include/StateMachine.h"
#include "../include/State.h"
#include <stdio.h>

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
	printf("Start engine\n");
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

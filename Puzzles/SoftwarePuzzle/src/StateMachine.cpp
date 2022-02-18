#include "States/InitializeState.h"
#include "States/CompletedState.h"
#include "States/HybernateState.h"
#include "States/RunningState.h"
#include "States/EntryState.h"
#include "StateMachine.h"
#include "State.h"
#include <Arduino.h>
#include <utility>

StateMachine::StateMachine() : 
	_all_states(
	{
	   	{INITIALIZE, new InitializeState},
	 	{HYBERNATE, new HybernateState},
		{ENTRY, new EntryState},
		{RUNNING, new RunningState},
		{COMPLETED, new CompletedState}
	})
{
	std::pair<EState, State *> firstState = std::make_pair(INITIALIZE, _all_states[INITIALIZE]);
	_current_state = &firstState;
}

void StateMachine::start_engine()
{
	Serial.println("Start engine\n");
	_all_states[INITIALIZE]->on_enter();
}

void StateMachine::change_state(EState eState)
{
	_all_states[_current_state->first]->on_exit();
	_previous_state = _current_state->first;

	_current_state->first = eState;
	_current_state->second = _all_states[eState];

	_all_states[eState]->on_enter();
}

EState StateMachine::get_current_state()
{
	return _current_state->first;
}

EState StateMachine::get_previous_state()
{
	return _previous_state;
}

#pragma once
#include <map>
#include <utility>
#include "State.h"

class State;

class StateMachine
{
public:
	// Singleton
	static StateMachine &instance()
	{
		static StateMachine INSTANCE;
		return INSTANCE;
	}

	void start_engine();
	void change_state(EState);
	void update();
	
	EState get_current_state();
	EState get_previous_state();
	
private:
	EState _previous_state;
	std::map<EState, State *> _all_states;
	std::pair<EState, State *> _current_state;

	StateMachine();
	virtual ~StateMachine() = default;

	friend class State;
};
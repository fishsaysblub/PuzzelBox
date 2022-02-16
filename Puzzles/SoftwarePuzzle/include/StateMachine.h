#include <map>
#include <utility>
#include "State.h"

#define number_of_input_pins 6
#define number_of_output_pins 6

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
	EState get_current_state();
	EState get_previous_state();

	int get_data_pin();
	int get_clock_pin();
	int get_latch_pin();

	int get_input_pin( int index );
	int get_output_pin( int index );

private:
	int data_pin;
	int clock_pin;
	int latch_pin;
	
	int _input_pins[number_of_input_pins];
	int _output_pins[number_of_output_pins];

	EState _previous_state;
	std::pair<EState, State *> *_current_state;
	std::map<EState, State *> _all_states;

	StateMachine();
	virtual ~StateMachine() = default;

	friend class State;
};
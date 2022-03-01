#pragma once
#include <map>
#include <utility>
#include "State.h"

/**
 * @brief Statemachine class used to handle all states and stateswiching.
 */
class StateMachine
{
public:
	/**
     * @brief Singleton to create a static instance.
     * 
     * @return StateMachine& returns static instance.
     */
	static StateMachine &instance()
	{
		static StateMachine INSTANCE;
		return INSTANCE;
	}

	/**
	 * @brief Starts statemachine in separete method to unwind stack.
	 */
	void start_engine();
	/**
	 * @brief Method can be called to switch to a new state and calls the on_enter and on_exit.
	 * 
	 * @param eState The next state which will be swiched to.
	 */
	void change_state(EState eState);
	/**
	 * @brief Method used to update the statemachine after a state swich.
	 * This function is necessary to prevent a stack overflow by unwinding the stack.
	 */
	void update();

	/**
	 * @brief Gets current EState.
	 * 
	 * @return EState returns _current_state.
	 */
	EState get_current_state();
	/**
	 * @brief Get previous EState.
	 * 
	 * @return EState return _previous_state.
	 */
	EState get_previous_state();
	
private:
	/**
	 * @brief Construct a new StateMachine object.
	 */
	StateMachine();
	/**
	 * @brief Destroy the State Machine object.
	 */
	virtual ~StateMachine();

	EState _previous_state; /*!< Previous state saved as EState. */
	std::map<EState, State *> _all_states; /*!< All Estates and states are saved in a map. */
	std::pair<EState, State *> _current_state; /*!< Current EState and *State saved as pair */

	friend class State;
};
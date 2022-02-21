#pragma once

/**
 * @brief All Statemachine states as enum.
 */
typedef enum
{
	INITIALIZE,
	HYBERNATE,
	ENTRY,
	RUNNING,
	COMPLETED
} EState;

/**
 * @brief Abstract state class.
 */
class State
{
public:
	/**
	 * @brief Method is called when entering a state.
	 */
	virtual void on_enter() = 0;
	/**
	 * @brief Update loop for a state.
	 */
	virtual void on_stay() = 0;
	/**
	 * @brief Method is called when exiting a state.
	 */
	virtual void on_exit() = 0;
};
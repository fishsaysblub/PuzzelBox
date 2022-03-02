#pragma once

/**
 * @brief All Statemachine states as enum.
 */
typedef enum
{
	INVALID,
	INITIALIZE, /*< Initialisation state */
	CHECK, /*< Check puzzles state */
	RUNNING, /*< Running state */
	COMPLETED /*< Completed state */
} EState;

/**
 * @brief Abstract state class.
 */
class State
{
public:
	/**
	 * @brief Destroy the a State object.
	 */
	virtual ~State() = default;

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
#pragma once
#include "State.h"

/**
 * @brief State in which the statemachine is after completing the puzzle.
 */
class CompletedState final : public State
{
public:
	/**
	 * @brief Construct a new Completed State object.
	 */
	CompletedState();
	/**
	 * @brief Destroy the Completed State object.
	 */
	virtual ~CompletedState();

	/**
	 * @brief Method initializes the Completed state.
	 */
	virtual void on_enter() override;
	/**
	 * @brief Method is the update loop of the Completed state.
	 */
	virtual void on_stay()  override;
	/**
	 * @brief Method to exit the Completed state.
	 */
	virtual void on_exit()  override;
};
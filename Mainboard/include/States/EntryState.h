#pragma once
#include "../State.h"

/**
 * @brief State which the statemachine is in
 * after first time hybernating or resetting the puzzle.
 */
class EntryState final : public State
{
public:
	/**
	 * @brief Construct a new Entry State object.
	 */
	EntryState();
	/**
	 * @brief Destroy the Entry State object.
	 */
	virtual ~EntryState();

	/**
	 * @brief Method initializes the Entry state.
	 */
	virtual void on_enter() override;
	/**
	 * @brief Method is the update loop of the Entry state.
	 */
	virtual void on_stay()  override;
	/**
	 * @brief Method to exit the Entry state.
	 */
	virtual void on_exit()  override;
};
#pragma once
#include "../State.h"

/**
 * @brief State used to initialize the embedded system and software.
 */
class InitializeState final : public State
{
public:
	/**
	 * @brief Construct a new Initialize State object.
	 */
	InitializeState();
	/**
	 * @brief Destroy the Initialize State object.
	 */
	virtual ~InitializeState();

	/**
	 * @brief Method initializes the Initialize state.
	 */
	virtual void on_enter() override;
	/**
	 * @brief Method is the update loop of the Initialize state.
	 */
	virtual void on_stay()  override;
	/**
	 * @brief Method to exit the Initialize state.
	 */
	virtual void on_exit()  override;
};
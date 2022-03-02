#pragma once
#include "../State.h"

class CheckState : public State
{
public:
    /**
     * @brief Construct a new Check State object.
     */
    CheckState();
    /**
     * @brief Destroy the Check State object.
     */
    ~CheckState();

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
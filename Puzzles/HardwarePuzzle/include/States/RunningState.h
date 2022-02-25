#pragma once
#include "State.h"

/**
 * @brief State which handles the user playing/solving the Software puzzle.
 */
class RunningState final : public State
{
public:
	/**
	 * @brief Construct a new Running State object.
	 */
	RunningState();
	/**
	 * @brief Destroy the Running State object
	 */
	virtual ~RunningState();
	
	/**
	 * @brief Method initializes the Running state.
	 */
	virtual void on_enter() override;
	/**
	 * @brief Method is the update loop of the Running state.
	 */
	virtual void on_stay()  override;
	/**
	 * @brief Method to exit the Running state.
	 */
	virtual void on_exit()  override;

	/**
	 * @brief Method gets the user inputs. 
	 * These are which banana plugs are connected to wich input.
	 */
	void get_user_input();
	/**
	 * @brief Method checks if all banana plugs are plugged in correctly.
	 * 
	 * @return true When alle banana plugs are in correct input.
	 * @return false When not alle banana plugs are plugged in correctly or are not coneccted.
	 */
	void puzzle_finished();

	/**
	 * @brief Method used for debugging.
	 * Method can be used to check if display is functioning correctly.
	 */
	void test_display();
};
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
	 * @brief Method checks if puzzle is finished if finished state is switched to completed.
	 */
	void check_puzzle_finished();
};
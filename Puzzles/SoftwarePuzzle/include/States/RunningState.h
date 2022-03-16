#pragma once
#include "Utils.h"
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
	 * @brief Method sets the correct output array.
	 * 
	 * @param ouput_array Array used to set _correct_output array.
	 */
	void set_correct_output(int *ouput_array);
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
	 * Method can be used to print the how the banana plugs are connected. 
	 */
	void print_output_values();
	/**
	 * @brief Method used for debugging.
	 * Method can be used to test the shiftregisters by alternating between leds every 400ms.
	 */
	void test_leds_and_shiftregisters();

private:	
	Utils _utils; /*!< Utility instance used in a test function. */

	int _check_list[6]; /*!< An array used to check if all banana plugs are connected at the right position. */
	int _input_values[6]; /*!< An array to save all the input states. */
	int _correct_output[6]; /*!< An array conaining the desired output to complete the puzzle. */
};
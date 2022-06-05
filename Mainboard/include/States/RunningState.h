#pragma once
#include "../State.h"

#define NUMBER_OF_PUZZLES 5

/**
 * @brief State which handles the user playing/solving the puzzles.
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
	 */
	void get_user_input();
	/**
	 * @brief Method renders leds strips dependant on user inputs.
	 */
	void render_ledstrip();
	/**
	 * @brief Method checks if all puzzles are completed.
	 */
	void are_puzzles_finished();

private:
	bool _box_is_on_surface; /*!< A boolean which is true if the box is on a surface and false if the box is lifted off a surface. */
	bool _box_was_on_surface; /*!< Single execution limitor for box on surface change. */
	bool _puzzles_finished_list[NUMBER_OF_PUZZLES]; /*!< List where which saves for each puzzle if it is completed. */
};
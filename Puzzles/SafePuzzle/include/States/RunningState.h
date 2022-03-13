#pragma once
#include "State.h"
#include "GpioManager.h"
#include <Keypad.h>

// Keypad def
#define LEVELS 5
#define ROWS 4
#define COLS 3

/**
 * @brief State which handles the user playing/solving the Safe puzzle.
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
	virtual void on_stay() override;
	/**
	 * @brief Method to exit the Running state.
	 */
	virtual void on_exit() override;

private:
	/**************************************************************
	 * @brief Check pressed key for level
	 *
	 * @return true Key pressed is correct
	 * @return false Key pressed is incorrect
	 **************************************************************/
	bool check_user_input();

	/**************************************************************
	 * @brief Set the level indication lights
	 *
	 **************************************************************/
	void set_level_indication();

	/**************************************************************
	 * @brief Display requested input code on the segment display
	 *
	 **************************************************************/
	void set_display_code();

	/**************************************************************
	 * @brief Check if all levels completed
	 * 
	 * @return true All levels have been completed
	 * @return false Not all levels have been completed
	 **************************************************************/
	bool check_puzzle_finished();

	/**************************************************************
	 * @brief Seven segment key pair struct
	 * Only for used Within class context
	 **************************************************************/
	struct Display_keys
	{
		char _disp1_key; /*!< Display 1 character */
		char _disp2_key; /*!< Display 2 character */
	};

	/**************************************************************
	 * @brief Keypad constants
	 * Keypad position and pin references
	 **************************************************************/
	const byte _ROW_PINS[ROWS] = {ROW_PIN1, ROW_PIN2, ROW_PIN3, ROW_PIN4};
	const byte _COL_PINS[COLS] = {COL_PIN1, COL_PIN2, COL_PIN3};
	const char _KEYS[ROWS][COLS] = {
		{'1', '2', '3'},
		{'4', '5', '6'},
		{'7', '8', '9'},
		{'*', '0', '#'}};

	Keypad *_keypad;			 /*!< Keypad instance */
	uint8_t _level_counter;		 /*!< Game stage counter */
	bool _levels_completed;		 /*!< All levels completed state */
	char *_code;				 /*!< Code to be checked */
	Display_keys *_code_display; /*!< Code display combinations */
};
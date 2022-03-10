#pragma once
#include "State.h"
#include "GpioManager.h"
#include <Keypad.h>

// Keypad def
#define LEVELS 5
#define ROWS 4
#define COLS 3

// Seven segment def	  	//Common Anode    //Common Cathode
#define DISP_0 B00000011 	// B00000011       B11111100
#define DISP_1 B10011111 	// B10011111       B01100000
#define DISP_2 B00100101 	// B00100101       B11011010
#define DISP_3 B00001101 	// B00001101       B11110010
#define DISP_4 B10011001 	// B10011001       B01100110
#define DISP_5 B01001001 	// B01001001       B10110110
#define DISP_6 B01000001 	// B01000001       B10111110
#define DISP_7 B00011111 	// B00011111       B11100000
#define DISP_8 B00000001 	// B00000001       B11111110
#define DISP_9 B00001001 	// B00001001       B11110110
#define DISP_A B00010001 	// B00010001       B11101110
#define DISP_C B01100011 	// B01100011       B10011100
#define DISP_E B01100001 	// B01100001       B10011110
#define DISP_F B01110001 	// B01110001       B10001110
#define DISP_H B10010001 	// B10010001       B01101110
#define DISP_L B11100011 	// B11100011       B00011100
#define DISP_P B00110001 	// B00110001       B11001110
#define DISP_U B10000011 	// B10000011       B01111100
#define DISP_DEFSTATE B11111111

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
	 * @brief Write bit string to seven segment display
	 *
	 * @param index Seven segment display index (0 or 1)
	 * @param key Character to write to display
	 **************************************************************/
	void write_to_display(uint8_t index, char key);

	/**************************************************************
	 * @brief Check if all levels completed
	 * 
	 * @return true All levels have been completed
	 * @return false Not all levels have been completed
	 **************************************************************/
	bool check_puzzle_finished();

	/**************************************************************
	 * @brief Seven segment key pair struct
	 *
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
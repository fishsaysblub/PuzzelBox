#pragma once
#include <Arduino.h>
#include "State.h"
#include "Utils.h"

#define LONG_TONE_DURATION 1000
#define SHORT_TONE_DURATION 250

#define MAX_NUMBER_DISPLAY 10
#define MORSE_CODE_NUMBER_LENGTH 5
#define COMPLETED_LOGIC_GATES_VALUE 0xB6

#define MORSE_CODE (int[10][5]) \
{					 		 	\
	{0, 0, 0, 0, 0}, /* 0 */ 	\
	{1, 0, 0, 0, 0}, /* 1 */ 	\
	{1, 1, 0, 0, 0}, /* 2 */ 	\
	{1, 1, 1, 0, 0}, /* 3 */ 	\
	{1, 1, 1, 1, 0}, /* 4 */ 	\
	{1, 1, 1, 1, 1}, /* 5 */ 	\
	{0, 1, 1, 1, 1}, /* 6 */ 	\
	{0, 0, 1, 1, 1}, /* 7 */ 	\
	{0, 0, 0, 1, 1}, /* 8 */ 	\
	{0, 0, 0, 0, 1}  /* 9 */ 	\
}

typedef enum
{
	NOTSTARTED,
	LOGICGATES,
	MORSECODE,
} EGamestage;

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
	 * @brief Method generates 4 random numbers which is set as _correct_potentiometer_values.
	 */
	void generate_random_four_digit_code();
	/**
	 * @brief Method changes the current game stage.
	 * 
	 * @param gameStage Gamestate which will be swiched to.
	 */
	void change_gamestage(EGamestage gameStage);
	/**
	 * @brief Method plays morse code on buzzer which student need to translate and set the potentiometers to.
	 */
	void play_morse_code();
	/**
	 * @brief Method plays tone by creating a PWM signal at the frequency 500 Hc;
	 * 
	 * @param duration Duration of the tone;
	 */
	void play_tone(int duration);
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
	/**
	 * @brief Method used for debugging.
	 * Method can be used to print the readings from the potentiometers.
	 */
	void test_potentiometers();

private:
	Utils utils;

	EGamestage _current_gamestage;

	byte _logic_gate_values;
	int _potentiometer_values[4];
	int _correct_potentiometer_values[4];
};
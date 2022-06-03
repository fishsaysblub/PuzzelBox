#pragma once
#include <Arduino.h>
#include "State.h"
#include "Utils.h"

#define BUZZER_FREQUENCY_OFF  0
#define BUZZER_FREQUENCY_ON 440

#define BREAK_TIME 2000
#define LONG_PAUZE 1000
#define SHORT_PAUZE 250
#define SHORT_TONE_DURATION 250
#define LONG_TONE_DURATION 1000

#define ANALOG_POTENTIOMETER_DIVISION_VALUE 450
#define MAX_NUMBER_DISPLAY 10
#define MORSE_CODE_LENGTH 4
#define MORSE_CODE_NUMBER_LENGTH 5
#define CORRECT_LOGIC_GATES_VALUE (int[8]){0, 1, 1, 0, 0, 0, 1, 0}

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
	int play_morse_code();
	/**
	 * @brief Method plays tone by creating a PWM signal at the frequency 500 Hz.
	 * 
	 * @param frequency The frequency of the tone.
	 * @param duration Duration of the tone.
	 */
	void play_tone(int duration, int frequency);
	/**
	 * @brief Method gets the user inputs. 
	 * These are which banana plugs are connected to wich input.
	 */
	void get_user_input();
	void render();
	/**
	 * @brief Method checks if all banana plugs are plugged in correctly.
	 * 
	 * @return true When alle banana plugs are in correct input.
	 * @return false When not alle banana plugs are plugged in correctly or are not coneccted.
	 */
	void puzzle_check();
	
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

	std::string _code;
	int _logic_gate_values[8];

	bool _tone_playing;

	int _morse_code_step;
	int _morse_code_number_step;

	int _ms_delay;

	int _potentiometer_values[4];
	int _correct_potentiometer_values[4];
};
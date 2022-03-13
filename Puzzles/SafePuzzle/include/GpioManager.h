/**************************************************************
 * @file GpioManager.h
 * @author Jef B (hj.baars@student.avans.nl)
 * @brief 
 * @version 0.1
 * @date 2022-03-10
 * 
 * @copyright Copyright (c) 2022
 * 
 **************************************************************/
#pragma once
#include <Arduino.h>

/**************************************************************
 * @brief Pin defines
 * ! TBD Need hardware info for shift pins
 * 
 **************************************************************/
#define ROW_PIN1 2
#define ROW_PIN2 3
#define ROW_PIN3 4
#define ROW_PIN4 5
#define COL_PIN1 6
#define COL_PIN2 7
#define COL_PIN3 8
#define LVLLED1 1
#define LVLLED2 2
#define LVLLED3 3
#define LVLLED4 4
#define LVLLED5 5
#define DISP_DATA1 1
#define DISP_CLK1 2
#define DISP_DATA2 3
#define DISP_CLK2 4

/**************************************************************
 * @brief Display defines
 * Seven segment def	  	Common Anode      Common Cathode
 **************************************************************/
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
 * @brief Class used to manage all IO.
 */
class GpioManager final
{
public:
    /**
     * @brief Singleton to create a static instance.
     * 
     * @return GpioManager& returns static instance.
     */
	static GpioManager &instance()
	{
		static GpioManager INSTANCE;
		return INSTANCE;
	}

	/**************************************************************
	 * @brief Set the level leds coresponding to the level
	 * 
	 * @param level Correct keys
	 **************************************************************/
	void set_level_leds(uint8_t level);

	/**************************************************************
	 * @brief Write bit string to seven segment display
	 *
	 * @param index Seven segment display index (0 or 1)
	 * @param key Character to write to display
	 **************************************************************/
	void write_to_display(uint8_t index, char key);

private:
	/**
	 * @brief Construct for Gpio Manager object.
	 */
    GpioManager();
	/**
	 * @brief Destroy the Gpio Manager object
	 * 
	 */
    virtual ~GpioManager() = default;
};
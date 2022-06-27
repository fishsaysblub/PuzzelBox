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
#include <TM1637Display.h>

/**************************************************************
 * @brief Pin defines
 * 
 **************************************************************/
#define ROW_PIN1 37		//! TOUCH PIN 37 external pull-up needed
#define ROW_PIN2 38		//! TOUCH PIN 38 external pull-up needed
#define ROW_PIN3 34
#define ROW_PIN4 35
#define COL_PIN1 19
#define COL_PIN2 21
#define COL_PIN3 22
#define LVLLED1 1
#define LVLLED2 2
#define LVLLED3 3
#define LVLLED4 23
#define LVLLED5 25
#define DISP_DATA1 14
#define DISP_CLK1 13
#define LOCK_PIN 26

/**************************************************************
 * @brief Display defines
 * Seven segment def
 **************************************************************/
#define DISP_0 B00111111
#define DISP_1 B00000110
#define DISP_2 B01011011
#define DISP_3 B01001111
#define DISP_4 B01100110
#define DISP_5 B01101101
#define DISP_6 B01111101
#define DISP_7 B00000111
#define DISP_8 B01111111
#define DISP_9 B01101111
#define DISP_A B01110111
#define DISP_C B00111001
#define DISP_E B01111001
#define DISP_F B01110001
#define DISP_H B01110110
#define DISP_L B00111000
#define DISP_P B01110011
#define DISP_U B00111110
#define DISP_N B00110111
#define DISP_DEFSTATE B00111111

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
	 * @param keys Characters to write to display
	 **************************************************************/
	void write_to_display(char *keys);

	/**************************************************************
	 * @brief Open the door of the safe for 20 seconds
	 * 
	 **************************************************************/
	void open_door();

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

	TM1637Display *_display;
};
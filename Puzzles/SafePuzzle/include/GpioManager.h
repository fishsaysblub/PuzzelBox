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

/**************************************************************
 * @brief Pin defines
 * 
 **************************************************************/
#define ROW_PIN1 2
#define ROW_PIN2 3
#define ROW_PIN3 4
#define ROW_PIN4 5
#define COL_PIN1 6
#define COL_PIN2 7
#define COL_PIN3 8

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
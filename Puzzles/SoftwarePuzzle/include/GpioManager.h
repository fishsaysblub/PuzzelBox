/**************************************************************
 * @file GpioManager.h
 * @author Julian de Bruin (jybruin@avans.nl)
 * @brief 
 * @version 0.1
 * @date 2022-02-22
 * 
 * @copyright Copyright (c) 2022
 * 
 **************************************************************/
#pragma once
#define PIN_COUNT_IO 6

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

	/**
	 * @brief Get the data pin.
	 * 
	 * @return int returns the data pin number.
	 */
    int get_data_pin();
	/**
	 * @brief Get the clock pin number.
	 * 
	 * @return int returns the clock pin number.
	 */
	int get_clock_pin();
	/**
	 * @brief Get the latch pin.
	 * 
	 * @return int returns the latch pin number.
	 */
	int get_latch_pin();
	
	/**
	 * @brief Get the input pin from _input_pins[]
	 * 
	 * @param index The index is used to select the pin from array.
	 * @return int Returns the selected input pin number.
	 */
	int get_input_pin( int index );
	/**
	 * @brief Get the output pin object
	 * 
	 * @param index 
	 * @return int 
	 */
	int get_output_pin( int index );

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

	int _data_pin; /*!< Pin used to send the data to shiftregister. */
	int _clock_pin; /*!< Pin used to clock in the data to the shiftregsiter. */
	int _latch_pin; /*!< Pin used display data in shiftregister to output pins. */
	
	int _input_pins[6]; /*!< Array of input pins. */
	int _output_pins[6]; /*!< Array of output pins. */
};
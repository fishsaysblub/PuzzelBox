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

#define MR_PIN 2
#define OE_PIN 26

#define CLK_PIN 14
#define DATA_PIN 27
#define LATCH_PIN 13

#define INPUTS (int[6]){39,36,35,34,38,37}
#define OUTPUTS (int[6]){25,19,23,18,10,9}

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
	 * @brief Method initializes the shiftregister.
	 */
	void initialize_shiftregister();
	/**
	 * @brief Method displays a uint16_t value in binary on 16 leds trough two cascaded shiftregisters.
	 * 
	 * @param value Integer value which is converted to binary and rendered.
	 */
	void render_leds( uint16_t value);

	/**
	 * @brief Set the clk pin with value.
	 * 
	 * @param value Value writen to pin.
	 */
    void set_clk_pin( bool value );
	/**
	 * @brief Set the data pin with value.
	 * 
	 * @param value Value writen to pin.
	 */
    void set_data_pin( bool value );
	/**
	 * @brief Set the latch pin with value.
	 * 
	 * @param value Value writen to pin.
	 */
    void set_latch_pin( bool value );
	
	/**
	 * @brief Get the value from an input pin from INPUTS[].
	 * 
	 * @param index The index is used to select the pin from the input array.
	 * @return int Returns the value from the input pin.
	 */
	int get_input_pin_value(int index);
	
	
	void set_output_pin(int index, bool value);

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

	/**
	 * @brief Union used to split unit16_t value into two bytes for each shiftresiter.
	 */
	union LedValues
	{
		uint16_t value; /*!< Value which will be displayed over 16 leds. */
		uint8_t byte_one; /*<! First eight bits of 16 bit value */
		uint8_t byte_two; /*<! Seccond eight bits of 16 bit value */
	};
};
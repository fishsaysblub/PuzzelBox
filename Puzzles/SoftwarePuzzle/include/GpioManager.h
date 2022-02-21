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
	 * @brief Setting up GPIO all pins.
	 */
	void setup_pins();

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
    virtual ~GpioManager() = default;

	int _data_pin;
	int _clock_pin;
	int _latch_pin;
	
	int _input_pins[6];
	int _output_pins[6];
};
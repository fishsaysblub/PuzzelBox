#pragma once
#include <TM1637Display.h>

//TODO: Set pins correctly

#define BUZZER_PIN		  0

#define DATA_PIN_BUTTONS  0
#define CLOCK_PIN_BUTTONS 0
#define LATCH_PIN_BUTTONS 0

#define DATA_PIN_DISPLAY  GPIO_NUM_14
#define CLOCK_PIN_DISPLAY GPIO_NUM_27

#define NUMBER_OF_POTENTIOMETERS 4
#define POTENTIOMETERS (int[NUMBER_OF_POTENTIOMETERS]){21, 22, 19, 23}
#define MAX_BRIGHTNESS 0x0F

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
	 * @brief Set the display value without trailing zeros at the front.
	 * 
	 * @param value Value displayed on the 4 digit seven segment display mus be from 0 to 9999.
	 */
	void set_display_value(int value);
	/**
	 * @brief Get the display instance.
	 * 
	 * @return TM1637Display Returns display instance;
	 */
	TM1637Display get_display_instance();

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
	 * @brief Class used to controll the 4 digit 7 segment display.
	 */
	TM1637Display display;
};
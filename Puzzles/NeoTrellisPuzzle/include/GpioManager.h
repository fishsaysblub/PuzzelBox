#pragma once
#include "Wire.h"

#define SDA_PIN 13
#define SCL_PIN 14

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
	 * @brief Method sets esp32 into sleep mode.
	 */
	void start_esp_sleep();

	/**
	 * @brief Set the neotrellis i2c pins.
	 * 
	 * @param wire Wire opject used to set pins.
	 */
	void set_neotrellis_i2c_pins(TwoWire *wire);

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
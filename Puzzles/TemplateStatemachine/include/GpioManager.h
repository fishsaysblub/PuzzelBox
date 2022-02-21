#pragma once

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

private:
	/**
	 * @brief Construct for Gpio Manager object.
	 */
    GpioManager();
    virtual ~GpioManager() = default;
};
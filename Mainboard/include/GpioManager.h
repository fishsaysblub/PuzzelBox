#pragma once

#define LDR_PIN 25

#define CLK_PIN 3
#define DATA_PIN 2
#define INTERRUPT_PIN 4

#define LED_STRIP_R 27 // 16
#define LED_STRIP_B 28 // 20
#define LED_STRIP_G 29 // 21

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
	 * @brief Reads the digital value of LDR.
	 * 
	 * @return true Light on LDR is very low.
	 * @return false Light on LDR is very high.
	 */
	bool read_ldr();

	/**
	 * @brief Method sets RGB values of the ledstrip.
	 * 
	 * @param r Red value.
	 * @param b Blue value.
	 * @param g Green value.
	 */
	void set_ledstrip(bool r, bool b, bool g);

	/**
	 * @brief Ident blink
	 */
	void blink_leds();

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
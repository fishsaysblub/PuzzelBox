#pragma once

#include "State.h"
#include "Adafruit_NeoTrellis.h"

#define X_LENGTH 8
#define Y_LENGTH 8

#define UPPER_LEFT_I2C_ADDR  0x2E
#define UPPER_RIGHT_I2C_ADDR 0x2F
#define LOWER_LEFT_I2C_ADDR  0x30
#define LOWER_RIGHT_I2C_ADDR 0x32

/**
 * @brief State which handles the user playing/solving the Software puzzle.
 */
class RunningState final : public State
{
public:
	static RunningState &instance()
	{
		static RunningState INSTANCE;
		return INSTANCE;
	}
	
	/**
	 * @brief Method initializes the Running state.
	 */
	virtual void on_enter() override;
	/**
	 * @brief Method is the update loop of the Running state.
	 */
	virtual void on_stay()  override;
	/**
	 * @brief Method to exit the Running state.
	 */
	virtual void on_exit()  override;

	/**
	 * @brief Method gets the user inputs. 
	 * These are which banana plugs are connected to wich input.
	 */
	void get_user_input();
	/**
	 * @brief Method checks if puzzle is finished if finished state is switched to completed.
	 */
	void check_puzzle_finished();

	/**
	 * @brief Get the color value.
	 * 
	 * @param colorValue Byte with color information.
	 * @return uint32_t Returns NeoPixel color in uint32_t.
	 */
	uint32_t get_color_value(byte colorValue);
	
	TrellisCallback handle_key_press(keyEvent event);

private:
	/**
	 * @brief Construct a new Running State object.
	 */
	RunningState();
	/**
	 * @brief Destroy the Running State object
	 */
	virtual ~RunningState();

	bool _matrix[X_LENGTH][Y_LENGTH]; /*!< Matrix which represents the current state of the neotrellis */
};
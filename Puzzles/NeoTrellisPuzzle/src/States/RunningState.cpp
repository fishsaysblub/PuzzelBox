#include <string>
#include <Arduino.h>
#include "GpioManager.h"
#include "StateMachine.h"
#include "States/RunningState.h"

#include "Wire.h"

TwoWire *wire = new TwoWire(1);

Adafruit_NeoTrellis t_array[Y_LENGTH/4][X_LENGTH/4] = 
{
	{
		Adafruit_NeoTrellis(UPPER_LEFT_I2C_ADDR , wire), 
		Adafruit_NeoTrellis(UPPER_RIGHT_I2C_ADDR, wire)
	},
	{
		Adafruit_NeoTrellis(LOWER_LEFT_I2C_ADDR , wire), 
		Adafruit_NeoTrellis(LOWER_RIGHT_I2C_ADDR, wire)
	}
};

static Adafruit_MultiTrellis _trellis((Adafruit_NeoTrellis *)t_array, Y_LENGTH/4, X_LENGTH/4);

RunningState::RunningState() :
	_matrix {
		{0, 0, 1, 0, 0, 0, 1, 1},
		{0, 1, 1, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 1, 1, 0, 0},
		{1, 1, 0, 1, 0, 0, 0, 0},
		{1, 0, 1, 0, 0, 1, 0, 0},
		{0, 0, 0, 1, 1, 0, 0, 0}
	},
	_reset_matrix {
		{0, 0, 1, 0, 0, 0, 1, 1},
		{0, 1, 1, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 1, 1, 0, 0},
		{1, 1, 0, 1, 0, 0, 0, 0},
		{1, 0, 1, 0, 0, 1, 0, 0},
		{0, 0, 0, 1, 1, 0, 0, 0}
	}	
{
	GpioManager::instance().set_neotrellis_i2c_pins(wire);
}

RunningState::~RunningState()
{

}

uint32_t RunningState::get_color_value(byte colorValue)
{
	if (colorValue < 85) 
	{
		return seesaw_NeoPixel::Color(colorValue * 3, 255 - colorValue * 3, 0);
	} 
	else if (colorValue < 170)
	{
		colorValue -= 85;
		return seesaw_NeoPixel::Color(255 - colorValue * 3, 0, colorValue * 3);
	} 
	else 
	{
		colorValue -= 170;
		return seesaw_NeoPixel::Color(0, colorValue * 3, 255 - colorValue * 3);
	}
	
	return -1;
}

TrellisCallback key_press(keyEvent event)
{
	return RunningState::instance().handle_key_press(event);
}

TrellisCallback RunningState::handle_key_press(keyEvent event)
{
	uint8_t xkey = event.bit.NUM%8;
	uint8_t ykey = event.bit.NUM/8;

	if (event.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING)
	{
		_matrix[ykey][xkey] = !_matrix[ykey][xkey];
		
		if (ykey > 0)
		{
			_matrix[ykey-1][xkey] = !_matrix[ykey-1][xkey];
		}
		if (ykey < 7)
		{
			_matrix[ykey+1][xkey] = !_matrix[ykey+1][xkey];
		}
		if (xkey > 0)
		{
			_matrix[ykey][xkey-1] = !_matrix[ykey][xkey-1];
		}
		if (xkey < 7)
		{
			_matrix[ykey][xkey+1] = !_matrix[ykey][xkey+1];
		}

		for (uint8_t y = 0; y < Y_LENGTH; y++) 
		{
			for (uint8_t x = 0; x < X_LENGTH; x++) 
			{
				//activate rising and falling edges on all keys
				_trellis.activateKey(x, y, SEESAW_KEYPAD_EDGE_RISING, true);
				_trellis.registerCallback(x, y, &key_press);
			
				// Set beginning game status 
				if (_matrix[y][x])
				{
					_trellis.setPixelColor(x, y, get_color_value(map((x+1)*(y+1), 0, X_LENGTH * Y_LENGTH, 0, 255)));
				}
				else if (!_matrix[y][x])
				{
					_trellis.setPixelColor(x, y, 0x000000);
				}
			
				_trellis.show(); //show all LEDs
				delay(5);
			}
		}
	}

	return 0;
}

void RunningState::on_enter()
{
	Serial.println("Enter Running");

	memcpy(_matrix, _reset_matrix, sizeof(_reset_matrix));

	while ( !_trellis.begin() ){};
	
	Serial.println("Started");

	for (uint8_t y = 0; y < Y_LENGTH; y++) {
		for (uint8_t x = 0; x < X_LENGTH; x++) {
			//activate rising and falling edges on all keys
			_trellis.activateKey(x, y, SEESAW_KEYPAD_EDGE_RISING, true);
			_trellis.activateKey(x, y, SEESAW_KEYPAD_EDGE_FALLING, true);
			_trellis.registerCallback(x, y, &key_press);

			// Set beginning game status 
			if (_matrix[y][x])
			{
				_trellis.setPixelColor(x, y, 0x00FF00);
			}
			else if (!_matrix[y][x])
			{
				_trellis.setPixelColor(x, y, 0x000000);
			}
			
			_trellis.show();
			delay(5);
		}
	}

	on_stay();
}

void RunningState::on_stay()
{
	get_user_input();
	check_puzzle_finished();
}


void RunningState::get_user_input()
{
	_trellis.read();
	delay(20);
}

void RunningState::check_puzzle_finished()
{
	for (int i = 0; i < Y_LENGTH; i++)
	{
		for (int j = 0; j < Y_LENGTH; j++)
		{
			if (_matrix[i][j])
			{
				return;
			}
		}
	}

	for (int i = 0; i < Y_LENGTH * X_LENGTH; i++) 
	{
		_trellis.setPixelColor(i, get_color_value(map(i, 0, Y_LENGTH * X_LENGTH, 0, 255))); //addressed with keynum
		_trellis.show();
		delay(40);
	}

	StateMachine::instance().change_state(COMPLETED);
}

void RunningState::on_exit()
{
	Serial.println("Exit Running\n");
}

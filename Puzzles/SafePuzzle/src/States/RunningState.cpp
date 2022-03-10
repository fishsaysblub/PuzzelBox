#include <string>
#include <Arduino.h>
#include "StateMachine.h"
#include "States/RunningState.h"

RunningState::RunningState() : _level_counter(0), _levels_completed(false)
{
	_keypad = new Keypad(makeKeymap(_KEYS), (byte *)_ROW_PINS, (byte *)_COL_PINS, (byte)ROWS, (byte)COLS);
	_code = new char[LEVELS]{0};
	_code_display = new Display_keys[LEVELS]{{0}};
}

RunningState::~RunningState()
{
	delete _keypad;
	delete _code;
	delete _code_display;
}

void RunningState::on_enter()
{
	Serial.println("Enter Running");
	_level_counter = 0;
	set_display_code();
	// TODO: Set display & load code data
}

void RunningState::on_stay()
{
	if (check_user_input())
	{
		_level_counter++;
		check_puzzle_finished();
	}
	else
	{
		_level_counter = 0;
	}
	set_level_indication();
	set_display_code();
}

bool RunningState::check_user_input()
{
	if (_level_counter >= sizeof(_code))
	{
		return false;
	}

	char key = _keypad->getKey();
	if (key != NO_KEY)
	{
		Serial.println(key);
		if (_code[_level_counter] == key)
		{
			return true;
		}
	}

	return false;
}

void RunningState::set_level_indication()
{
	if (_level_counter >= 0)
	{
		// SET LED1
	}
	if (_level_counter >= 1)
	{
		// SET LED2
	}
	if (_level_counter >= 2)
	{
		// SET LED3
	}
	if (_level_counter >= 3)
	{
		// SET LED4
	}
	if (_level_counter >= 4)
	{
		// SET LED5
	}
}

void RunningState::set_display_code()
{
	if (_level_counter >= sizeof(_code_display))
	{
		return;
	}

	write_to_display(0, _code_display[_level_counter]._disp1_key);
	write_to_display(1, _code_display[_level_counter]._disp2_key);
}

void RunningState::write_to_display(uint8_t index, char key)
{
	//! TBD Need hardware info for shift pins
	uint8_t data_pin = 1;
	uint8_t clk_pin = 2;
	if (index >= 1)
	{
		data_pin = 3;
		clk_pin = 4;
	}

	switch (key)
	{
	case '1':
		shiftOut(data_pin, clk_pin, LSBFIRST, DISP_1);
		break;
	case '2':
		shiftOut(data_pin, clk_pin, LSBFIRST, DISP_2);
		break;
	case '3':
		shiftOut(data_pin, clk_pin, LSBFIRST, DISP_3);
		break;
	case '4':
		shiftOut(data_pin, clk_pin, LSBFIRST, DISP_4);
		break;
	case '5':
		shiftOut(data_pin, clk_pin, LSBFIRST, DISP_5);
		break;
	case '6':
		shiftOut(data_pin, clk_pin, LSBFIRST, DISP_6);
		break;
	case '7':
		shiftOut(data_pin, clk_pin, LSBFIRST, DISP_7);
		break;
	case '8':
		shiftOut(data_pin, clk_pin, LSBFIRST, DISP_8);
		break;
	case '9':
		shiftOut(data_pin, clk_pin, LSBFIRST, DISP_9);
		break;
	case '0':
		shiftOut(data_pin, clk_pin, LSBFIRST, DISP_0);
		break;
	case 'A':
		shiftOut(data_pin, clk_pin, LSBFIRST, DISP_A);
		break;
	case 'C':
		shiftOut(data_pin, clk_pin, LSBFIRST, DISP_C);
		break;
	case 'E':
		shiftOut(data_pin, clk_pin, LSBFIRST, DISP_E);
		break;
	case 'F':
		shiftOut(data_pin, clk_pin, LSBFIRST, DISP_F);
		break;
	case 'H':
		shiftOut(data_pin, clk_pin, LSBFIRST, DISP_H);
		break;
	case 'L':
		shiftOut(data_pin, clk_pin, LSBFIRST, DISP_L);
		break;
	case 'P':
		shiftOut(data_pin, clk_pin, LSBFIRST, DISP_P);
		break;
	case 'U':
		shiftOut(data_pin, clk_pin, LSBFIRST, DISP_U);
		break;
	default:
		shiftOut(data_pin, clk_pin, LSBFIRST, DISP_DEFSTATE);
		break;
	}
}

bool RunningState::check_puzzle_finished()
{
	if (_level_counter == LEVELS)
	{
		_levels_completed = true;
		StateMachine::instance().change_state(COMPLETED);
		return true;
	}

	return false;
}

void RunningState::on_exit()
{
	Serial.println("Exit Running\n");
}

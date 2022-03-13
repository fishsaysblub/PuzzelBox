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
	// TODO: Set display & load code data from Communication (Retreived in an earlier state)
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
	GpioManager::instance().set_level_leds(_level_counter);
}

void RunningState::set_display_code()
{
	if (_level_counter >= sizeof(_code_display))
	{
		return;
	}

	GpioManager::instance().write_to_display(0, _code_display[_level_counter]._disp1_key);
	GpioManager::instance().write_to_display(1, _code_display[_level_counter]._disp2_key);
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

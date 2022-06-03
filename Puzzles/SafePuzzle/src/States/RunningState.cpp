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
	_code[0] = '1';
	_code[1] = '2';
	_code[2] = '3';
	_code[3] = '4';
	_code[4] = '5';

	_code_display[0]._disp1_key = 'A';
	_code_display[0]._disp2_key = '1';
	_code_display[1]._disp1_key = 'H';
	_code_display[1]._disp2_key = '8';
	_code_display[2]._disp1_key = 'U';
	_code_display[2]._disp2_key = '0';
	_code_display[3]._disp1_key = 'P';
	_code_display[3]._disp2_key = '3';
	_code_display[4]._disp1_key = 'C';
	_code_display[4]._disp2_key = '6';

	set_display_code();
	// TODO: Set display & load code data from Communication (Retreived in an earlier state)
}

void RunningState::on_stay()
{
	int inputCheck = check_user_input();
	if (inputCheck == KEY_CORRECT)
	{
		_level_counter++;
		check_puzzle_finished();
		Serial.printf("Correct Lvl UP : %d\n", _level_counter);
	}
	else if (inputCheck == KEY_INCORRECT)
	{
		_level_counter = 0;
		Serial.printf("Incorrect.. %d\n", _level_counter);
	}
	set_level_indication();
	set_display_code();
}

int RunningState::check_user_input()
{
	if (_level_counter >= LEVELS)
	{
		return KEY_NONE;
	}

	char key = _keypad->getKey();
	if (key != NO_KEY)
	{
		Serial.printf("Key pressed %c Code: %c\n", key, _code[_level_counter]);
		if (_code[_level_counter] == key)
		{
			return KEY_CORRECT;
		}
		else
		{
			return KEY_INCORRECT;
		}
	}

	return KEY_NONE;
}

void RunningState::set_level_indication()
{
	GpioManager::instance().set_level_leds(_level_counter);
}

void RunningState::set_display_code()
{
	if (_level_counter >= LEVELS)
	{
		return;
	}
	char codes[2] = {_code_display[_level_counter]._disp1_key, _code_display[_level_counter]._disp2_key};
	GpioManager::instance().write_to_display(codes);
}

bool RunningState::check_puzzle_finished()
{
	if (_level_counter >= LEVELS)
	{
		Serial.println("Levels completed\n");
		_levels_completed = true;
		GpioManager::instance().open_door();
		StateMachine::instance().change_state(COMPLETED);
		return true;
	}

	return false;
}

void RunningState::on_exit()
{
	Serial.println("Exit Running\n");
}

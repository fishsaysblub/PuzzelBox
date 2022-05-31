#include <string>
#include <Arduino.h>
#include "GpioManager.h"
#include "StateMachine.h"
#include "States/RunningState.h"

RunningState::RunningState() :
	_current_gamestage(NOTSTARTED),
	_code(""),
	_logic_gate_values(0),
	_tone_playing(false),
	_morse_code_step(0),
	_morse_code_number_step(0),
	_ms_delay(0),
	_potentiometer_values{},
	_correct_potentiometer_values{}
{
}

RunningState::~RunningState()
{
}

void RunningState::generate_random_four_digit_code()
{
	Serial.print("Generatring random morse code...\nCode: ");

	for (int i = 0; i < MORSE_CODE_LENGTH; i++) 
	{
		_correct_potentiometer_values[i] = random(10);
		_code += utils.int_to_string(_correct_potentiometer_values[i]);
  	}

	Serial.print(_code.c_str());
	Serial.print("\n");
}

void RunningState::on_enter()
{
	Serial.println("Enter Running");
	generate_random_four_digit_code();	
	GpioManager::instance();

	change_gamestage(LOGICGATES);
}

void RunningState::render()
{
	if (_ms_delay == 0)
	{
		_ms_delay = millis() + play_morse_code();
	}
	else if (millis() >= _ms_delay)
	{
		_ms_delay = 0;
	}

	if (_current_gamestage == MORSECODE)
	{
		int values = _potentiometer_values[0] * 1000 +
					 _potentiometer_values[1] * 100  +
					 _potentiometer_values[2] * 10   +
					 _potentiometer_values[3] * 1    ;

		GpioManager::instance().set_display_value(values);
	}
}

void RunningState::on_stay()
{
	get_user_input();
	render();
	puzzle_check();
}

void RunningState::change_gamestage(EGamestage gameStage)
{
	_current_gamestage = gameStage;
}

int RunningState::play_morse_code()
{
	if (_current_gamestage == MORSECODE)
	{
		if (_morse_code_step < NUMBER_OF_POTENTIOMETERS)
		{
			if (_morse_code_number_step < MORSE_CODE_NUMBER_LENGTH)
			{
				if (!_tone_playing)
				{
					_tone_playing = true;

					if (MORSE_CODE[_correct_potentiometer_values[_morse_code_step]][_morse_code_number_step])
					{
						GpioManager::instance().set_buzzer_pin(440);
						return LONG_TONE_DURATION;
					}
					else
					{
						GpioManager::instance().set_buzzer_pin(440);
						return SHORT_TONE_DURATION;
					}
				}
				else
				{
					GpioManager::instance().set_buzzer_pin(0);
					_tone_playing = false;
					_morse_code_number_step++;
					return SHORT_PAUZE;
				}
			}
			else
			{
				_morse_code_number_step = 0;
				_morse_code_step++;
				return LONG_PAUZE;
			}
		}
		else
		{
			_morse_code_step = 0;
			return BREAK_TIME;
		}
	}

	return 0;
}

void RunningState::get_user_input()
{
	if (_current_gamestage == LOGICGATES)
	{
		Serial.print("Button values: ");
		digitalWrite( LATCH_PIN_BUTTONS, LOW  );
		digitalWrite( CLKIN_PIN_BUTTONS, HIGH );
		delay(20);
		digitalWrite( LATCH_PIN_BUTTONS, HIGH );
		digitalWrite( CLKIN_PIN_BUTTONS, LOW  );

		for ( int i = 0; i < 8; i++ )
		{
			if(digitalRead(DATA_PIN_BUTTONS))
			{
				Serial.print( "1" );
			}
			else
			{
				Serial.print( "0" );
			}

			digitalWrite(CLOCK_PIN_BUTTONS, HIGH);
			digitalWrite(CLOCK_PIN_BUTTONS, LOW);
		}

		Serial.print("\n");
		delay(50);
	}
	else if (_current_gamestage == MORSECODE)
	{
		for (int i = 0; i < NUMBER_OF_POTENTIOMETERS; i++)
		{
			int analogValue = (analogRead(POTENTIOMETERS[i]) / ANALOG_POTENTIOMETER_DIVISION_VALUE) + 1;
			analogValue = ((analogValue - MAX_NUMBER_DISPLAY) * -1);
			_potentiometer_values[i] = analogValue;
		}
	}
}

void RunningState::puzzle_check()
{
	if (_current_gamestage == LOGICGATES)
	{
		if (_logic_gate_values == CORRECT_LOGIC_GATES_VALUE)
		{
			change_gamestage(MORSECODE);
		}
	}
	else if (_current_gamestage == MORSECODE)
	{
		for (int i = 0; i < MORSE_CODE_LENGTH; i++)
		{
			if (_correct_potentiometer_values[i] != _potentiometer_values[i])
			{
				return;
			}
		}
		
		GpioManager::instance().set_buzzer_pin(BUZZER_FREQUENCY_OFF);
		StateMachine::instance().change_state(COMPLETED);
	}
}

void RunningState::on_exit()
{
	Serial.println("Exit Running\n");
}

void RunningState::test_display()
{
	for (int i = 0; i <= 1000; i++)
	{
		GpioManager::instance().set_display_value(i);
	}
}

void RunningState::test_potentiometers()
{
	Serial.print("Code: ");
	Serial.print( _code.c_str() );
	Serial.print(" Potentiometers: ");

	for (int i = 0; i < NUMBER_OF_POTENTIOMETERS; i++)
	{
		std::string output = " P" + utils.int_to_string(i) + ": " + utils.int_to_string(_potentiometer_values[i]);
		Serial.print(output.c_str());
	}

	Serial.print("\n");
}
#include <string>
#include <Arduino.h>
#include "GpioManager.h"
#include "StateMachine.h"
#include "States/RunningState.h"

RunningState::RunningState() :
	_current_gamestage(NOTSTARTED),
	_logic_gate_values(0xB6),
	_potentiometer_values{},
	_correct_potentiometer_values{}
{
}

RunningState::~RunningState()
{
}

void RunningState::generate_random_four_digit_code()
{
	for (int i = 0; i < NUMBER_OF_POTENTIOMETERS; i++) 
	{
		_correct_potentiometer_values[i] = rand() % MAX_NUMBER_DISPLAY;
  	}
}

void RunningState::on_enter()
{
	Serial.println("Enter Running");
	generate_random_four_digit_code();	
	change_gamestage(LOGICGATES);
}

void RunningState::on_stay()
{
	play_morse_code();
	get_user_input();
	puzzle_finished();
}

void RunningState::change_gamestage(EGamestage gameStage)
{
	_current_gamestage = gameStage;
}

void RunningState::play_tone(int duration)
{
	for ( int i = 0; i < ( duration / 2 ); i++)
	{
		digitalWrite(BUZZER_PIN, HIGH);
		delay(1);
		digitalWrite(BUZZER_PIN, LOW);
		delay(1);
	}
}

void RunningState::play_morse_code()
{
	if (_current_gamestage == MORSECODE)
	{
		Serial.println("Playing morse code...");

		for (int i = 0; i < NUMBER_OF_POTENTIOMETERS; i++)
		{
			for (int j = 0; j < MORSE_CODE_NUMBER_LENGTH; j++)
			{
				if (MORSE_CODE[_correct_potentiometer_values[i]][j])
				{
					play_tone(LONG_TONE_DURATION);
				}
				else
				{
					play_tone(SHORT_TONE_DURATION);
				}

				delay(50);
			}

			delay(400);
		}

		delay(1000);
	}
}

void RunningState::get_user_input()
{
	if (_current_gamestage == LOGICGATES)
	{
		// digitalWrite(LATCH_PIN_BUTTONS, LOW);
		// _logic_gate_values = shiftIn(DATA_PIN_BUTTONS, CLOCK_PIN_BUTTONS, MSBFIRST);
		// digitalWrite(LATCH_PIN_BUTTONS, HIGH);
	}
	else if (_current_gamestage == MORSECODE)
	{
		for (int i = 0; i < NUMBER_OF_POTENTIOMETERS; i++)
		{
			// _potentiometer_values[i] = analogRead(POTENTIOMETERS[i]); //TODO:: Devide by 10
		}

		test_potentiometers();
	}
}

void RunningState::puzzle_finished()
{
	if (_current_gamestage == LOGICGATES)
	{
		if (_logic_gate_values == COMPLETED_LOGIC_GATES_VALUE)
		{
			change_gamestage(MORSECODE);
		}
	}
	else if (_current_gamestage == MORSECODE)
	{
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
		delay(10);
	}
}

void RunningState::test_potentiometers()
{
	Serial.print("Potentiometers: ");

	for (int i = 0; i < NUMBER_OF_POTENTIOMETERS; i++)
	{
		std::string output = " P" + utils.int_to_string(i) + ": " + utils.int_to_string(_potentiometer_values[i]);
		Serial.print(output.c_str());
	}

	Serial.print("\n");

	delay(100);
}
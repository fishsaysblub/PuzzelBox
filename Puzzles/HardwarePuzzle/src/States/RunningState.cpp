#include <string>
#include <Arduino.h>
#include "GpioManager.h"
#include "StateMachine.h"
#include "States/RunningState.h"

RunningState::RunningState()
{
}

RunningState::~RunningState()
{
}

void RunningState::on_enter()
{
	Serial.println("Enter Running");
}

void RunningState::on_stay()
{
	test_display();
	get_user_input();
	puzzle_finished();
}

void RunningState::get_user_input()
{

}

void RunningState::puzzle_finished()
{
	if (true)
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
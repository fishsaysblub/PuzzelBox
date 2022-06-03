#include "../../include/States/RunningState.h"
#include "../../include/StateMachine.h"
#include "../../include/GpioManager.h"
#include <wiringPi.h>
#include <stdio.h>
#include <string>

RunningState::RunningState():
	_box_is_on_surface(false),
	_puzzles_finished_list{}
{
}

RunningState::~RunningState()
{
}

void RunningState::on_enter()
{
	printf("Enter Running\n");
}

void RunningState::on_stay()
{
	//get_user_input();
	//render_ledstrip();
	are_puzzles_finished();
}

void RunningState::get_user_input()
{
	_box_is_on_surface = GpioManager::instance().read_ldr();

	for(int i = 0; i < NUMBER_OF_PUZZLES; i++) //TODO: Replace with callback which sets this list
	{
		_puzzles_finished_list[i] = true;
	}
}

void RunningState::render_ledstrip()
{
	if (_box_is_on_surface)
	{
		GpioManager::instance().set_ledstrip(LOW, LOW, HIGH);
	}
	else
	{
		GpioManager::instance().set_ledstrip(HIGH, LOW, LOW);
	}
}

void RunningState::are_puzzles_finished()
{
	bool finished = true;

	for(int i = 0; i < NUMBER_OF_PUZZLES; i++)
	{
		if ( !_puzzles_finished_list[i] )
		{
			finished = false;
			break;
		}
	}

	if (finished)
	{
		StateMachine::instance().change_state(COMPLETED);
	}
}

void RunningState::on_exit()
{
	printf("Exit Running\n\n");
}
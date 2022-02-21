#pragma once
#include "Utils.h"
#include "State.h"

class RunningState final : public State
{
public:
	RunningState();
	virtual ~RunningState();
	
	virtual void on_enter() override;
	virtual void on_stay()  override;
	virtual void on_exit()  override;

	void set_correct_output(int ouput_array[6]);

	void get_user_input();
	bool check_completed();
	void render_leds(uint16_t value);

	// For debugging / testing
	void printOutputValues();
	void test_leds_and_shiftregisters();

private:
	Utils utils;

	int _check_list[6];
	int _output_values[6];
	int _correct_output[6];
};
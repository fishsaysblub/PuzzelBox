#include "State.h"

class RunningState final : public State
{
public:
	RunningState();
	virtual ~RunningState();

	void get_user_input();
	bool check_completed();
	void render_leds(uint16_t value);

	virtual void on_enter() override;
			void on_stay();
	virtual void on_exit() override;

	// void set_output_values( int index );
	// int get_output_values( int index );

private:
	bool _check_list[6];
	bool _output_values[6];
};
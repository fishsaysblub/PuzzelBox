#pragma once
#define PIN_COUNT_IO 6

class GpioManager final
{
public:
    // Singleton
	static GpioManager &instance()
	{
		static GpioManager INSTANCE;
		return INSTANCE;
	}

	void start_manager();
	void setup_pins();

    int get_data_pin();
	int get_clock_pin();
	int get_latch_pin();

	int get_input_pin( int index );
	int get_output_pin( int index );

private:
    GpioManager();
    virtual ~GpioManager();

	int _data_pin;
	int _clock_pin;
	int _latch_pin;
	
	int _input_pins[6];
	int _output_pins[6];
};
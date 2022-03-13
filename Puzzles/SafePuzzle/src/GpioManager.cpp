#include "GpioManager.h"

GpioManager::GpioManager()
{
    pinMode(LVLLED1, OUTPUT);
    pinMode(LVLLED2, OUTPUT);
    pinMode(LVLLED3, OUTPUT);
    pinMode(LVLLED4, OUTPUT);
    pinMode(LVLLED5, OUTPUT);

    pinMode(DISP_DATA1, OUTPUT);
    pinMode(DISP_DATA2, OUTPUT);
    pinMode(DISP_CLK1, OUTPUT);
    pinMode(DISP_CLK2, OUTPUT);
}

void GpioManager::set_level_leds(uint8_t level)
{
    if (level >= 0)
		digitalWrite(LVLLED1, HIGH);
	else
        digitalWrite(LVLLED1, LOW);
	if (level >= 1)
		digitalWrite(LVLLED2, HIGH);
	else
        digitalWrite(LVLLED2, LOW);
    if (level >= 2)
		digitalWrite(LVLLED3, HIGH);
	else
        digitalWrite(LVLLED3, LOW);
    if (level >= 3)
		digitalWrite(LVLLED4, HIGH);
	else
        digitalWrite(LVLLED4, LOW);
    if (level >= 4)
		digitalWrite(LVLLED5, HIGH);
	else
        digitalWrite(LVLLED5, LOW);
}

void GpioManager::write_to_display(uint8_t index, char key)
{
    uint8_t data_pin = DISP_DATA1;
    uint8_t clk_pin = DISP_CLK2;
    if (index >= 1)
    {
        data_pin = DISP_DATA2;
        clk_pin = DISP_CLK2;
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
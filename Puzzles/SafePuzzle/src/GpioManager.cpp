#include "GpioManager.h"

GpioManager::GpioManager()
{
    pinMode(LVLLED1, OUTPUT);
    pinMode(LVLLED2, OUTPUT);
    pinMode(LVLLED3, OUTPUT);
    pinMode(LVLLED4, OUTPUT);
    pinMode(LVLLED5, OUTPUT);
    pinMode(LOCK_PIN, OUTPUT);

    digitalWrite(LOCK_PIN, HIGH);

    pinMode(ROW_PIN1, INPUT_PULLUP);
    pinMode(ROW_PIN2, INPUT_PULLUP);
    pinMode(ROW_PIN3, INPUT_PULLUP);
    pinMode(ROW_PIN4, INPUT_PULLUP);


    _display = new TM1637Display(DISP_CLK1, DISP_DATA1);
    _display->setBrightness(0x02);
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

void GpioManager::write_to_display(char *keys)
{
    uint8_t segments[4] = {0x00, 0x00, 0x00, 0x00};

    for (int i = 0; i < 2; i++)
    {
        switch (keys[i])
        {
        case '1':
            segments[i+1] = DISP_1;
            break;
        case '2':
            segments[i+1] = DISP_2;
            break;
        case '3':
            segments[i+1] = DISP_3;
            break;
        case '4':
            segments[i+1] = DISP_4;
            break;
        case '5':
            segments[i+1] = DISP_5;
            break;
        case '6':
            segments[i+1] = DISP_6;
            break;
        case '7':
            segments[i+1] = DISP_7;
            break;
        case '8':
            segments[i+1] = DISP_8;
            break;
        case '9':
            segments[i+1] = DISP_9;
            break;
        case '0':
            segments[i+1] = DISP_0;
            break;
        case 'A':
            segments[i+1] = DISP_A;
            break;
        case 'C':
            segments[i+1] = DISP_C;
            break;
        case 'E':
            segments[i+1] = DISP_E;
            break;
        case 'F':
            segments[i+1] = DISP_F;
            break;
        case 'H':
            segments[i+1] = DISP_H;
            break;
        case 'L':
            segments[i+1] = DISP_L;
            break;
        case 'P':
            segments[i+1] = DISP_P;
            break;
        case 'U':
            segments[i+1] = DISP_U;
            break;
        default:
            segments[i+1] = DISP_DEFSTATE;
            break;
        }
    }

    _display->setSegments(segments);
}

void GpioManager::open_door() 
{
    digitalWrite(LOCK_PIN, HIGH);

    uint8_t segments[4] = {DISP_0, DISP_P, DISP_E, DISP_N};
    _display->setSegments(segments);

    delay(20000);

    digitalWrite(LOCK_PIN, LOW);
    uint8_t leeg[4] = {0};
    
    _display->setSegments(leeg);
}
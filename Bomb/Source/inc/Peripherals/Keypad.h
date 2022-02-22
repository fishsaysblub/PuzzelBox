//
// Created by david on 14-5-19.
//

#ifndef MAIN_BOM_KEYPAD_H
#define MAIN_BOM_KEYPAD_H

#define PRESSED 0x80u
#define KEY_NUMBER 0x7F

#define IS_PRESSED(KEY) (((KEY)&PRESSED) == PRESSED)
#define GET_KEY(KEY) ((KEY)&KEY_NUMBER)

#include "Gpio.h"

namespace Peripherals
{
    class Keypad
    {
    public:
        Keypad();
        ~Keypad() = default;

    public:
        enum Key
        {
            NONE,
            KEY1,
            KEY2,
            KEY3,
            KEY4,
            KEY5,
            KEY6,
            KEY7,
            KEY8,
            KEY9,
            KEY0,
            KEY_ASTERISK,
            KEY_HASH_TAG,
            KEY_CAD,
        };

    public:
        bool Check();
        enum Key GetKey();

    private:
        enum Key m_key;
        Gpio m_columns[3];
        Gpio m_rows[4];

    private:
        static bool SimulateCheck();
        enum Key SimulateKey();

        bool Scan();
        enum Key DecodeMatrix(Gpio &column, Gpio &row);
    };
};

#endif // MAIN_BOM_KEYPAD_H

//
// Created by david on 14-5-19.
//

#include <iostream>
#include <limits>
#include <poll.h>
#include <Config.h>
#include <chrono>
#include <thread>
#include "Peripherals/Keypad.h"

Peripherals::Keypad::Keypad()
    : m_key(NONE),
      m_columns{
          Gpio(Gpio::C1, Gpio::OUT),
          Gpio(Gpio::C2, Gpio::OUT),
          Gpio(Gpio::C3, Gpio::OUT),
      },
      m_rows{
          Gpio(Gpio::R1, Gpio::IN),
          Gpio(Gpio::R2, Gpio::IN),
          Gpio(Gpio::R3, Gpio::IN),
          Gpio(Gpio::R4, Gpio::IN),
      }
{

    for (Gpio &gpio : m_columns)
    {
        gpio.SetValue(GPIO_HIGH);
    }
}

bool Peripherals::Keypad::Check()
{
#if SIMULATION
    return SimulateCheck();
#else
    return Scan();
#endif
}

Peripherals::Keypad::Key Peripherals::Keypad::GetKey()
{
#if SIMULATION
    return SimulateKey();
#else
    return m_key;
#endif
}

bool Peripherals::Keypad::SimulateCheck()
{
    pollfd cinfd[1];
    // Theoretically this should always be 0, but one fileno call isn't going to hurt, and if
    // we try to run somewhere that stdin isn't fd 0 then it will still just work
    cinfd[0].fd = fileno(stdin);
    cinfd[0].events = POLLIN;

    return poll(cinfd, 1, 10);
}

Peripherals::Keypad::Key Peripherals::Keypad::SimulateKey()
{
    std::string key;
    std::cin >> key;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (key == "0")
        return KEY0;
    if (key == "1")
        return KEY1;
    if (key == "2")
        return KEY2;
    if (key == "3")
        return KEY3;
    if (key == "4")
        return KEY4;
    if (key == "5")
        return KEY5;
    if (key == "6")
        return KEY6;
    if (key == "7")
        return KEY7;
    if (key == "8")
        return KEY8;
    if (key == "9")
        return KEY9;
    if (key == "*")
        return KEY_ASTERISK;
    if (key == "#")
        return KEY_HASH_TAG;

    return NONE;
}

bool Peripherals::Keypad::Scan()
{
    enum Key keys[3] = {NONE};
    int iKey = 0;

    for (Gpio &column : m_columns)
    {
        column.SetValue(GPIO_LOW);

        for (Gpio &row : m_rows)
        {
            if (row.GetValue() == GPIO_LOW)
            {
                column.SetValue(GPIO_HIGH);

                keys[iKey++] = DecodeMatrix(column, row);

                if (iKey == 1 && keys[0] == KEY_ASTERISK)
                {
                    std::cout << "CAD 1" << std::endl;
                    continue;
                }
                if (iKey == 2 && keys[1] == KEY5)
                {
                    std::cout << "CAD 2" << std::endl;
                    continue;
                }
                if (iKey == 3 && keys[2] == KEY3)
                {
                    std::cout << "CAD 3 => ACTIVE CAD" << std::endl;

                    if (m_key == KEY_CAD)
                        return false;
                    m_key = KEY_CAD;
                    return true;
                }

                if (keys[0] == m_key)
                    return false;
                m_key = keys[0];
                return true;
            }
        }

        column.SetValue(GPIO_HIGH);
    }

    if (iKey > 0)
    {
        if (keys[0] == m_key)
            return false;

        m_key = keys[0];
        return true;
    }

    m_key = NONE;
    return false;
}

Peripherals::Keypad::Key Peripherals::Keypad::DecodeMatrix(Peripherals::Gpio &column, Peripherals::Gpio &row)
{
    switch (row.GetPin())
    {
    case Gpio::R1:
        switch (column.GetPin())
        {
        case Gpio::C1:
            return KEY1;
        case Gpio::C2:
            return KEY2;
        case Gpio::C3:
            return KEY3;
        default:
            return NONE;
        }
    case Gpio::R2:
        switch (column.GetPin())
        {
        case Gpio::C1:
            return KEY4;
        case Gpio::C2:
            return KEY5;
        case Gpio::C3:
            return KEY6;
        default:
            return NONE;
        }
    case Gpio::R3:
        switch (column.GetPin())
        {
        case Gpio::C1:
            return KEY7;
        case Gpio::C2:
            return KEY8;
        case Gpio::C3:
            return KEY9;
        default:
            return NONE;
        }
    case Gpio::R4:
        switch (column.GetPin())
        {
        case Gpio::C1:
            return KEY_ASTERISK;
        case Gpio::C2:
            return KEY0;
        case Gpio::C3:
            return KEY_HASH_TAG;
        default:
            return NONE;
        }
    default:
        return NONE;
    }
}

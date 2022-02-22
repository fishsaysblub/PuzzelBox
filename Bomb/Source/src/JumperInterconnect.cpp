//
// Created by david on 20-5-19.
//

#include <Peripherals/Keypad.h>
#include <iostream>
#include "JumperInterconnect.h"

#define ESC "\x1B\x5B"

JumperInterconnect::JumperInterconnect()
    : m_map{0}, m_current{0}
{
}

void JumperInterconnect::Monitor()
{
    int key = m_driver.CheckKey();
    if (key == -1)
        return;

    if (IS_PRESSED(key))
    {
        std::cout << GET_KEY(key) / 10 << "⇒ " << GET_KEY(key) % 10 << std::endl;
        m_current[GET_KEY(key) / 10] = GET_KEY(key) % 10;
    }
    else
    {
        std::cout << GET_KEY(key) / 10 << "⇒ " << 0 << std::endl;
        m_current[GET_KEY(key) / 10] = 0;
    }
}

bool JumperInterconnect::Correct()
{
    for (int i = 0; i < NUMBER_OF_JUMPER_COLUMNS; ++i)
    {
        if (m_current[i] != m_map[i])
            return false;
    }

    return true;
}

void JumperInterconnect::SetMap(const uint8_t *map)
{
    for (int i = 0; i < NUMBER_OF_JUMPER_COLUMNS; ++i)
    {
        m_map[i] = map[i];
    }
}

void JumperInterconnect::PrintMap()
{
    std::cout << ESC "0;0H" << std::flush;
    for (int i = 0; i < NUMBER_OF_JUMPER_COLUMNS; ++i)
    {
        std::cout << i << ": " << (int)m_current[i] << " MAP: " << (int)m_map[i] << std::string(15, ' ') << std::endl;
    }
}

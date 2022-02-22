//
// Created by david on 22-4-19.
//

#include <iostream>
#include <linux/spi/spidev.h>
#include "Peripherals/Display.h"

#define ESC "\x1B\x5B"

Peripherals::Display::Display()
    : m_status(BLACK), m_armed(BLACK), m_userInput{0}, m_iUserInput(5)
{
}

void Peripherals::Display::DisplaySegments(int *segments)
{
#if SIMULATION
    ShowToScreen(segments);
#else
    for (int i = 0; i < 6; ++i)
    {
        m_driver.SetSegment(5 - i, segments[i]);
    }
#endif
}

void Peripherals::Display::SetLed(Peripherals::Display::Led led, int value)
{
    bool update = false;
    switch (led)
    {
    case STATUS:
        if (m_status != value)
        {
            update = true;
        }
        m_status = value;
        break;
    case ARMED:
        if (m_armed != value)
        {
            update = true;
        }
        m_armed = value;
        break;
    }

#if !SIMULATION
    if (update)
        m_driver.SetLeds(m_armed, m_status);
#else
    (void)update;
#endif
}

void Peripherals::Display::Safe()
{
    int segments[6] = {0};
    segments[5] = 0b01101101; // S
    segments[4] = 0b01011111; // A
    segments[3] = 0b01110001; // F
    segments[2] = 0b01111001; // E

    SetLed(ARMED, BLACK);
    SetLed(STATUS, GREEN);
    DisplaySegments(segments);
}

void Peripherals::Display::Wait()
{
    static int pos = 0;
    int segments[6] = {0};
    if (pos < 6)
    {
        segments[pos] = 0x01;
    }
    else if (pos < 8)
    {
        segments[5] = 1u << (11u - pos);
    }
    else if (pos < 14)
    {
        segments[13 - pos] = 0x08;
    }
    else if (pos < 16)
    {
        segments[0] = 1u << (16u - pos);
    }

    if (++pos >= 16)
        pos = 0;

    DisplaySegments(segments);
}

void Peripherals::Display::Clear()
{
    int segments[6] = {0};
    DisplaySegments(segments);
}

int Peripherals::Display::To7Segment(int digit)
{
    switch (digit)
    {
    case 0:
        return 0x3f;
    case 1:
        return 0x06;
    case 2:
        return 0x5B;
    case 3:
        return 0x4F;
    case 4:
        return 0x66;
    case 5:
        return 0x6D;
    case 6:
        return 0x7D;
    case 7:
        return 0x07;
    case 8:
        return 0x7F;
    case 9:
        return 0x6F;
    default:
        return 0xFF;
    }
}

void Peripherals::Display::DisplayUserInputs()
{
    DisplaySegments(m_userInput);
}

void Peripherals::Display::SetUserInput(int segment)
{
    m_userInput[m_iUserInput] = segment;

    if (m_iUserInput > 0)
        m_iUserInput--;
}

void Peripherals::Display::ResetUserInput()
{
    m_iUserInput = 5;
    for (int &i : m_userInput)
    {
        i = 0;
    }
}

Peripherals::StLedDriver &Peripherals::Display::GetDriver()
{
    return m_driver;
}

void Peripherals::Display::ShowToScreen(int *segments)
{
    std::cout << ESC "0;0H" << std::flush;

    for (int line = 0; line < 3; ++line)
    {
        for (int j = 5; j >= 0; --j)
        {
            switch (line)
            {
            case 0:
                ShowSegmentToScreen(segments[j], 0);
                ShowSegmentToScreen(segments[j], 1);
                ShowSegmentToScreen(segments[j], 0);
                ShowSegmentToScreen(segments[j], 0);
                break;
            case 1:
                ShowSegmentToScreen(segments[j], 6);
                ShowSegmentToScreen(segments[j], 7);
                ShowSegmentToScreen(segments[j], 2);
                ShowSegmentToScreen(segments[j], 0);
                break;
            case 2:
                ShowSegmentToScreen(segments[j], 5);
                ShowSegmentToScreen(segments[j], 4);
                ShowSegmentToScreen(segments[j], 3);
                ShowSegmentToScreen(segments[j], 8);
                break;
            default:
                break;
            }
        }
        std::cout << std::endl;
    }
    SimulateLeds();
}

void Peripherals::Display::ShowSegmentToScreen(unsigned segment, unsigned index)
{
    unsigned mask = 0x01u << (index - 1);

    if ((segment & mask) != mask || index == 0)
    {
        std::cout << " ";
        return;
    }

    switch (index)
    {
    case 1:
    case 7:
    case 4:
        std::cout << "_";
        return;

    case 6:
    case 2:
    case 5:
    case 3:
        std::cout << "|";
        return;

    case 8:
        std::cout << ".";
        return;

    default:
        std::cout << "X";
        return;
    }
}

void Peripherals::Display::SimulateLeds()
{
    std::cout << "ARMED:\t" ESC << std::to_string(m_armed) << "m"
              << " ";
    std::cout << ESC "0m" << std::endl;
    std::cout << "STATUS:\t" ESC << std::to_string(m_status) << "m"
              << " ";
    std::cout << ESC "0m" << std::endl;
}

//
// Created by david on 19-5-19.
//

#include <Config.h>
#include <iostream>
#include "Peripherals/Tca8418Interface.h"

#define ADDRESS 0x34u

#define CFG 0x01u
#define OVR_FLOW_M (0x01u << 5u)
#define KE_IEN (0x01u << 0u)

#define INT_STAT 0x02u
#define K_INT (0x01u << 0u)

#define KEY_LCK_EC 0x03u
#define KEC3 (0x01u << 3u)
#define KEC2 (0x01u << 2u)
#define KEC1 (0x01u << 1u)
#define KEC0 (0x01u << 0u)
#define KEC (KEC3 | KEC2 | KEC1 | KEC0)

#define KEY_EVENT_A 0x04u

#define KP_GPIO1 0x1Du
#define ROW7 (0x01u << 7u)
#define ROW6 (0x01u << 6u)
#define ROW5 (0x01u << 5u)
#define ROW4 (0x01u << 4u)
#define ROW3 (0x01u << 3u)
#define ROW2 (0x01u << 2u)
#define ROW1 (0x01u << 1u)
#define ROW0 (0x01u << 0u)

#define KP_GPIO2 0x1Eu
#define COL7 (0x01u << 7u)
#define COL6 (0x01u << 6u)
#define COL5 (0x01u << 5u)
#define COL4 (0x01u << 4u)
#define COL3 (0x01u << 3u)
#define COL2 (0x01u << 2u)
#define COL1 (0x01u << 1u)
#define COL0 (0x01u << 0u)

#define KP_GPIO3 0x1Fu
#define COL9 (0x01u << 1u)
#define COL8 (0x01u << 0u)

#define DEBOUNCE_D1 0x29u
#define DEBOUNCE_D2 0x2Au
#define DEBOUNCE_D3 0x2Bu

Peripherals::TCA8418Interface::TCA8418Interface()
    : I2Cinterface("/dev/i2c-1"), m_interrupt(Gpio::JumperInterrupt, Gpio::IN)
{
    Setup();
}

int Peripherals::TCA8418Interface::CheckKey()
{
    if (AmountKeyChanged() == 0)
        return -1;

    return Read(ADDRESS, KEY_EVENT_A);
}

void Peripherals::TCA8418Interface::Setup()
{
    uint8_t cnf = OVR_FLOW_M | KE_IEN;
    Write(ADDRESS, CFG, cnf);

    Write(ADDRESS, KP_GPIO2, COL0 | COL1 | COL2 | COL3 | COL4 | COL5 | COL6 | COL7);
    Write(ADDRESS, KP_GPIO1, ROW0 | ROW1 | ROW2 | ROW3 | ROW4 | ROW5 | ROW6 | ROW7);
}

uint8_t Peripherals::TCA8418Interface::AmountKeyChanged()
{
    uint8_t interrupt;
    uint8_t events;

    if (m_interrupt.GetValue() == GPIO_HIGH)
        return 0;

    interrupt = Read(ADDRESS, INT_STAT);
    if ((interrupt & K_INT) != K_INT)
        return 0;

    events = Read(ADDRESS, KEY_LCK_EC) & KEC;

    if (events == 0)
        Write(ADDRESS, INT_STAT, K_INT);
    return events;
}

//
// Created by david on 19-5-19.
//

#ifndef MAIN_BOM_TCA8418_INTERFACE_H
#define MAIN_BOM_TCA8418_INTERFACE_H

#include "I2Cinterface.h"
#include "Gpio.h"

namespace Peripherals
{
    class TCA8418Interface : I2Cinterface
    {
    public:
        TCA8418Interface();
        ~TCA8418Interface() override = default;

    public:
        int CheckKey();

    private:
        Peripherals::Gpio m_interrupt;

    private:
        void Setup();
        uint8_t AmountKeyChanged();
    };
}

#endif // MAIN_BOM_TCA8418_INTERFACE_H

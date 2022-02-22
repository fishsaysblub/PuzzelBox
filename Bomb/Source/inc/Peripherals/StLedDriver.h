//
// Created by david on 18-5-19.
//

#ifndef MAIN_BOM_STLEDDRIVER_H
#define MAIN_BOM_STLEDDRIVER_H

#include "SpiInterface.h"
#include "Gpio.h"

#define CABLE_1 0x01u
#define CABLE_2 0x02u
#define CABLE_3 0x04u
#define CABLE_4 0x08u

namespace Peripherals
{
    class StLedDriver : SpiInterface
    {
    public:
        StLedDriver();
        ~StLedDriver() override = default;

    public:
        void SetSegment(uint8_t segment, uint8_t value);
        void SetLeds(uint8_t led1, uint8_t led2);
        uint8_t GetCableStates();

    private:
        Peripherals::Gpio m_writeEnable;
        Peripherals::Gpio m_readEnable;

    private:
        void Setup();
        void WriteToMemory(uint8_t address, uint8_t value);

        uint8_t TranslateColor(uint8_t color);
    };
};

#endif // MAIN_BOM_STLEDDRIVER_H

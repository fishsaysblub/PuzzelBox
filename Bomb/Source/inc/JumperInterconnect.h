//
// Created by david on 20-5-19.
//

#ifndef MAIN_BOM_JUMPERINTERCONNECT_H
#define MAIN_BOM_JUMPERINTERCONNECT_H

#include <Peripherals/Tca8418Interface.h>
#include "Config.h"

class JumperInterconnect
{
public:
    JumperInterconnect();
    ~JumperInterconnect() = default;

public:
    void Monitor();
    bool Correct();

    void SetMap(const uint8_t *map);
    void PrintMap();

private:
    Peripherals::TCA8418Interface m_driver;
    uint8_t m_map[NUMBER_OF_JUMPER_COLUMNS];
    uint8_t m_current[NUMBER_OF_JUMPER_COLUMNS];
};

#endif // MAIN_BOM_JUMPERINTERCONNECT_H

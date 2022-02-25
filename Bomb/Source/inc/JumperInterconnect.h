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
    /**************************************************************
     * @brief Construct a new Jumper Interconnect object
     * 
     **************************************************************/
    JumperInterconnect();

    /**************************************************************
     * @brief Destroy the Jumper Interconnect object
     * 
     **************************************************************/
    ~JumperInterconnect() = default;

public:
    /**************************************************************
     * @brief Read and store jumper inputs
     * 
     **************************************************************/
    void Monitor();

    /**************************************************************
     * @brief Check wire combination
     * 
     * @return true - Combination matches map
     * @return false - Does not match
     **************************************************************/
    bool Correct();

    /**************************************************************
     * @brief Set the Map object
     * 
     * @param map - Jumper link map
     **************************************************************/
    void SetMap(const uint8_t *map);

    /**************************************************************
     * @brief Debug print
     * 
     **************************************************************/
    void PrintMap();

private:
    Peripherals::TCA8418Interface m_driver;
    uint8_t m_map[NUMBER_OF_JUMPER_COLUMNS];
    uint8_t m_current[NUMBER_OF_JUMPER_COLUMNS];
};

#endif // MAIN_BOM_JUMPERINTERCONNECT_H

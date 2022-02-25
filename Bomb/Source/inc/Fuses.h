//
// Created by david on 15-5-19.
//

#ifndef MAIN_BOM_FUSES_H
#define MAIN_BOM_FUSES_H

#include <Peripherals/StLedDriver.h>
#include "Config.h"

/**************************************************************
 * @brief Wire puzzle class
 * 
 **************************************************************/
class Fuses
{
public:
    /**************************************************************
     * @brief Construct a new Fuses object
     * 
     * @param ledDriver - Hardware driver
     **************************************************************/
    Fuses(Peripherals::StLedDriver &ledDriver);

    /**************************************************************
     * @brief Destroy the Fuses object
     * 
     **************************************************************/
    ~Fuses() = default;

public:
    /**************************************************************
     * @brief Get the Active Fuses left
     * 
     * @return const unsigned - Codes left
     **************************************************************/
    const unsigned GetActiveFuses() const;

    /**************************************************************
     * @brief Get the Incorrect Codes count
     * 
     * @return const unsigned& - Mistakes
     **************************************************************/
    const unsigned &GetIncorrectCodes() const;

    /**************************************************************
     * @brief Get the Cable Bonus effect
     * 
     * @return const int& - Bonus
     **************************************************************/
    const int &GetCableBonus() const;

public:
    /**************************************************************
     * @brief Set the Min Codes amount
     * 
     * @param nCodes - Minimum amount of dismantle codes
     **************************************************************/
    void SetMinCodes(unsigned nCodes);

    /**************************************************************
     * @brief Set the Cable Filter mask
     * 
     * @param filter - Binary mask
     **************************************************************/
    void SetCableFilter(unsigned filter);

public:
    /**************************************************************
     * @brief Check user input code
     * 
     *TODO: This method should be updated to accept network generated codes.
     * 
     * @param code - Code from keypad
     * @return true - Code correct
     * @return false - Code incorrect
     **************************************************************/
    bool CheckCode(unsigned code);

    /**************************************************************
     * @brief Get the Cable Fuses effect
     * 
     * @return const unsigned - Positive or negative time modifier
     **************************************************************/
    const unsigned GetCableFuses();

private:
    Peripherals::StLedDriver &m_ledDriver;
    unsigned m_cables;
    unsigned m_cableFilter;
    int m_cableBonus;

    unsigned m_codes;
    unsigned m_minLimitCodes;
    unsigned m_incorrect;
    bool m_puzzles[NUMBER_OF_PUZZELS];

private:
    /**************************************************************
     * @brief Check code using algorithm 
     * 
     * @param code - User input code
     * @return true - Code returns correct checksum
     * @return false - Code fails checksum
     **************************************************************/
    bool ValidateCode(unsigned code);
    static bool CheckChecksum(unsigned idCode, unsigned random, unsigned checksumCode);

    /**************************************************************
     * @brief Load game data from file
     * 
     **************************************************************/
    void LoadFromFile();

    /**************************************************************
     * @brief Log game data to file
     * 
     **************************************************************/
    void SaveToFile();
};

#endif // MAIN_BOM_FUSES_H

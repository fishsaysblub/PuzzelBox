//
// Created by david on 15-5-19.
//

#ifndef MAIN_BOM_FUSES_H
#define MAIN_BOM_FUSES_H

#include <Peripherals/StLedDriver.h>
#include "Config.h"

class Fuses
{
public:
    Fuses(Peripherals::StLedDriver &ledDriver);
    ~Fuses() = default;

public:
    const unsigned GetActiveFuses() const;
    const unsigned &GetIncorrectCodes() const;
    const int &GetCableBonus() const;

public:
    void SetMinCodes(unsigned nCodes);
    void SetCableFilter(unsigned filter);

public:
    bool CheckCode(unsigned code);
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
    bool ValidateCode(unsigned code);
    static bool CheckChecksum(unsigned idCode, unsigned random, unsigned checksumCode);

    void LoadFromFile();
    void SaveToFile();
};

#endif // MAIN_BOM_FUSES_H

//
// Created by david on 22-4-19.
//

#ifndef MAIN_BOM_BOM_H
#define MAIN_BOM_BOM_H

#include <Peripherals/Display.h>
#include <Peripherals/Keypad.h>
#include <Peripherals/Sound.h>
#include "Fuses.h"
#include "JumperInterconnect.h"
#include <chrono>

typedef std::chrono::duration<int, std::ratio_multiply<std::chrono::hours::period, std::ratio<24>>::type> Days;

class Bom
{
public:
    /**************************************************************
     * @brief Construct a new Bom object
     * 
     **************************************************************/
    explicit Bom();

    /**************************************************************
     * @brief Destroy the Bom object
     * 
     **************************************************************/
    ~Bom() = default;

public:
    /**************************************************************
     * @brief Wait for device configuration
     * 
     * Reads .bom file from usb device and sets settings 
     **************************************************************/
    void WaitForArmed();

    /**************************************************************
     * @brief Wait until configured time has been reached for start
     * 
     **************************************************************/
    void WaitForCountdown();

    /**************************************************************
     * @brief Main game loop
     * 
     **************************************************************/
    void CountDown();

    /**************************************************************
     * @brief Wait for game end action
     * 
     **************************************************************/
    void WaitForClose();

private:
    unsigned m_startTime;
    time_t m_start;
    unsigned m_duration;
    Peripherals::Display m_display;
    Peripherals::Keypad m_keypad;
    Peripherals::Sound m_sound;
    JumperInterconnect m_jumpers;
    Fuses m_fuses;
    std::string m_file;
    bool m_displayError;

    int m_userInput;
    int m_iUserInput;
    bool m_userInputActive;

private:
    /**************************************************************
     * @brief Set the Countdown length
     * 
     * @param h - Hours
     * @param m - Minutes
     * @param s - Seconds
     **************************************************************/
    void SetCountdown(int h, int m, int s);

    /**************************************************************
     * @brief Set the Start Time 
     * 
     * @param h - Hours
     * @param m - Minutes
     * @param s - Seconds
     **************************************************************/
    void SetStartTime(int h, int m, int s);

    /**************************************************************
     * @brief Display updater thread
     * 
     * Run during CountDown()
     **************************************************************/
    void DisplayUpdater();

    /**************************************************************
     * @brief Extract time from chrono time
     * 
     * @param buffer - Output time buffer array
     * @param time - Chrono time
     * @param ms - Milliseconds
     * @return int* - Buffer
     **************************************************************/
    static int *ExtractTime(int *buffer, std::chrono::system_clock::duration time, int &ms);

    /**************************************************************
     * @brief Find and copy bomb file and start assembler
     * 
     * @param connection - Assembler
     * @param moveTo - File location
     **************************************************************/
    void SearchBomFile(AssembleConnection &connection, const std::string &moveTo = "./tmp.bom");

    /**************************************************************
     * @brief Find files in folder
     * 
     * @param dirName - Folder name
     * @return std::string - Found file name
     **************************************************************/
    static std::string SearchInDir(const std::string &dirName);

    /**************************************************************
     * @brief Check assembler error
     * 
     * @param connection - Assembler
     **************************************************************/
    void AssembleError(AssembleConnection &connection);

    /**************************************************************
     * @brief Encript data buffer
     * 
     * @param data - Data to encript int array size 8
     * @param buffer - Encripted data array
     * @return int* Buffer
     **************************************************************/
    static int *Encrypt(const int *data, int *buffer);

    /**************************************************************
     * @brief Check for .bomb file extension
     * 
     * @param filename - Filename to check
     * @return true - File extension is .bom
     * @return false - File extension not .bom
     **************************************************************/
    static bool HasExtension(char *filename);

    /**************************************************************
     * @brief Display time check
     * 
     * @param connection - Assembler
     * @param buffer - Bugger
     * @param ms - Time
     * @return AssembleConnection& Assembler
     **************************************************************/
    AssembleConnection &DisplayTime(AssembleConnection &connection, int *buffer, int ms);

    /**************************************************************
     * @brief Read key pad input
     * 
     **************************************************************/
    void ReadKeyPad();

    /**************************************************************
     * @brief Check user key pad input code
     * 
     **************************************************************/
    void CheckUserCode();

    /**************************************************************
     * @brief Generate time based feedback
     * 
     * @param ms - Current time
     * @param trigger - Trigger time
     * @param timeLeft - Countdown value
     * @return int Return Trigger
     **************************************************************/
    int ArmedNotifier(int ms, int trigger, const std::chrono::system_clock::duration &timeLeft);

    /**************************************************************
     * @brief Pregame display method
     * 
     * @param showCurrentTime - Time toggle Now / left
     * @param currentTime - Current time
     **************************************************************/
    void DrawWaitDisplay(int &showCurrentTime, const unsigned int &currentTime);

    /**************************************************************
     * @brief Apply settings from read file
     * 
     * @param settings - Settings data buffer int array size 7
     **************************************************************/
    void ApplySettings(const std::vector<int> &settings);
};

#endif // MAIN_BOM_BOM_H

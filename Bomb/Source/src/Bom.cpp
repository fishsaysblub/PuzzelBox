//
// Created by david on 22-4-19.
//

#include <ctime>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <AssembleConnection.h>
#include "Bom.h"
#include <dirent.h>
#include <sys/stat.h>

Bom::Bom()
    : m_startTime(0), m_start(0), m_duration(0), m_fuses(m_display.GetDriver()), m_file(""), m_displayError(false),
      m_userInput(0), m_iUserInput(0),
      m_userInputActive(false)
{
}

void Bom::WaitForArmed()
{
    AssembleConnection connection;
    std::vector<int> settings;
    int input[0];
    std::ifstream localSetup("./setup.bom");

    if (localSetup)
    {
        connection.StartAssembler("./setup.bom");
        m_file = "";
    }
    else
    {
        m_display.Safe();
    SEARCH:

        if (m_keypad.Check() && m_keypad.GetKey() == Peripherals::Keypad::KEY_CAD)
        {
            m_display.SetLed(Peripherals::Display::STATUS, YELLOW);
            system("modprobe -r g_ether dwc2;"
                   "sleep 5;"
                   "modprobe dwc2 g_ether;");
            m_display.SetLed(Peripherals::Display::STATUS, CYAN);
        }

        usleep(100 * 1000);
        SearchBomFile(connection, "./setup.bom");

        if (m_file.empty())
        {
            m_display.SetLed(Peripherals::Display::STATUS, CYAN);
            goto SEARCH;
        }
    }

    settings = connection.Execute(input, 0);
    if (settings.size() < 8 + NUMBER_OF_JUMPER_COLUMNS)
    {
        std::cout << "ERR SETUP " << connection.GetFeedback() << std::endl;
        std::cout << "#outputs " << settings.size() << std::endl;
        m_display.Safe();
        m_display.SetLed(Peripherals::Display::STATUS, RED);
        usleep(1000 * 1000);

        if (m_file == "./setup.bom")
            system("rm ./setup.bom");
        goto SEARCH;
    }

    ApplySettings(settings);

    std::cout << "Setup done" << std::endl;
}

void Bom::WaitForCountdown()
{
    bool toggle = false;
    int showCurrentTime = 1;

    m_start = time(nullptr);
    m_start -= m_start % 86400; // Remove hours
    m_start -= m_start % 3600;  // Remove minutes
    m_start -= m_start % 60;    // Remove seconds
    m_start += m_startTime;
    m_display.SetLed(Peripherals::Display::STATUS, BLACK);

    while (time(nullptr) <= m_start)
    {
        const unsigned currentTime = time(nullptr);
        if ((currentTime & 0x01u) == 0x01)
        {
            toggle = true;
        }
        else if (toggle)
        {
            toggle = false;
            m_display.SetLed(Peripherals::Display::ARMED, RED);
        }
        else
        {
            m_display.SetLed(Peripherals::Display::ARMED, BLACK);
        }

        DrawWaitDisplay(showCurrentTime, currentTime);

        usleep(1000 * 100);
    }
    std::cout << "START" << std::endl;
}

void Bom::CountDown()
{
    unsigned currentTime;
    std::thread displayer(&Bom::DisplayUpdater, this);

    try
    {
        for (unsigned i = 1; i <= m_fuses.GetIncorrectCodes(); ++i)
        {
            m_duration -= i * PENALTY_STEPS;
        }
        m_duration += CABLE_BONUS * m_fuses.GetCableBonus();

        m_display.SetLed(Peripherals::Display::STATUS, BLACK);
        while ((currentTime = time(nullptr)) < (m_start + m_duration) &&
               m_fuses.GetActiveFuses() > 0)
        {

            if (m_keypad.Check())
            {
                m_display.SetLed(Peripherals::Display::STATUS, BLUE);
                m_userInputActive = true;

                ReadKeyPad();
            }

            m_jumpers.Monitor();

            CheckUserCode();
            usleep(100 * 1000);
        }
        m_display.SetLed(Peripherals::Display::STATUS, BLACK);
        m_duration = 0;

        if (m_fuses.GetActiveFuses() > 0)
        {
            m_sound.Biem();
            std::cout << "Biem" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(4));
        }

        system("rm ./setup.bom");
        system("rm ./fuses");
        displayer.join();
    }
    catch (const char *err)
    {
        m_duration = 0;
        displayer.join();
    }
    catch (std::string &err)
    {
        m_duration = 0;
        displayer.join();
    }
    catch (std::exception &err)
    {
        m_duration = 0;
        displayer.join();
    }
}

void Bom::WaitForClose()
{
    while (true)
    {

        if (m_keypad.Check() && m_keypad.GetKey() == Peripherals::Keypad::KEY_CAD)
        {
            return;
        }
        usleep(100 * 1000);
    }
}

void Bom::SetCountdown(int h, int m, int s)
{
    m_duration = h * 3600 + m * 60 + s;
}

void Bom::SetStartTime(int h, int m, int s)
{
    m_startTime = h * 3600 + m * 60 + s;
}

void Bom::DisplayUpdater()
{
    AssembleConnection connection;
    int buffer[8] = {0};
    int ms = 0;
    int trigger = 0;
    std::chrono::system_clock::time_point end;
    std::chrono::system_clock::time_point end_copy;
    std::chrono::system_clock::duration timeLeft;

    while (m_duration > 0)
    {
        SearchBomFile(connection);
        end_copy = end;
        end = std::chrono::system_clock::from_time_t(m_start + m_duration);
        timeLeft = end - std::chrono::system_clock::now();

        ExtractTime(buffer, timeLeft, ms);
        trigger = ArmedNotifier(ms, trigger, timeLeft);

        if (m_iUserInput == -1)
        {
            m_display.Wait();
        }
        else if (m_userInputActive)
        {
            m_display.DisplayUserInputs();
        }
        else
        {
            connection = DisplayTime(connection, buffer, ms);
        }

        m_duration += m_fuses.GetCableFuses() * CABLE_BONUS;
        usleep(10 * 1000);
    }

    timeLeft = end - std::chrono::system_clock::now();
    if (timeLeft.count() < 0)
        ExtractTime(buffer, timeLeft.zero(), ms);
    else
        ExtractTime(buffer, timeLeft, ms);

    for (int i = 0; i < 6; ++i)
    {
        buffer[i] = Peripherals::Display::To7Segment(buffer[i]);
    }
    m_display.DisplaySegments(buffer);
}

int *Bom::ExtractTime(int *buffer, std::chrono::system_clock::duration time, int &ms)
{
    int offset;

    Days days;
    std::chrono::hours hour;
    std::chrono::minutes minutes;
    std::chrono::seconds seconds;
    std::chrono::milliseconds milliseconds;

    days = std::chrono::duration_cast<Days>(time);
    time -= days;

    hour = std::chrono::duration_cast<std::chrono::hours>(time);
    time -= hour;

    minutes = std::chrono::duration_cast<std::chrono::minutes>(time);
    time -= minutes;

    seconds = std::chrono::duration_cast<std::chrono::seconds>(time);
    time -= seconds;

    milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(time);
    time -= milliseconds;

    if (ms >= 0)
    {
        ms = milliseconds.count() / 10;
    }
    if (hour.count() == 0 && ms >= 0)
    {
        offset = 2;

        buffer[0] = ms % 10;
        buffer[1] = (ms / 10) % 10;
    }
    else
    {
        offset = 0;

        buffer[4] = hour.count() % 10;
        hour /= 10;
        buffer[5] = hour.count() % 10;
    }

    buffer[offset + 0] = seconds.count() % 10;
    seconds /= 10;
    buffer[offset + 1] = seconds.count() % 10;

    buffer[offset + 2] = minutes.count() % 10;
    minutes /= 10;
    buffer[offset + 3] = minutes.count() % 10;

    buffer[6] = ms % 10;
    buffer[7] = (ms / 10) % 10;

    return buffer;
}

void Bom::SearchBomFile(AssembleConnection &connection, const std::string &moveTo)
{
    std::string file = SearchInDir("/media/");
    struct stat buffer
    {
    };
    int testBuffer[8] = {0};

    if (file == m_file && !m_file.empty())
    {
        return;
    }
    else if (file.empty())
    {
        // Check if file exists
        if (stat(moveTo.c_str(), &buffer) == 0)
        {
            if (m_file != moveTo)
            {
                m_file = moveTo;
                connection.StartAssembler(moveTo);
            }
        }
        else
        {
            m_file = "";
        }
        return;
    }

    m_file = moveTo;
    m_displayError = false;

    system(("cp " + file + " " + moveTo).c_str());
    connection.StartAssembler(moveTo);

    // Perform test before umounting
    std::vector<int> processed;
    processed = connection.Execute(testBuffer, 8);

    if (processed.empty())
    {
        AssembleError(connection);
    }

    system("umount /media/*");
    std::cout << "USB FREE" << std::endl;
}

std::string Bom::SearchInDir(const std::string &dirName)
{
    DIR *d;
    struct dirent *dir;
    std::string name;

    d = opendir(dirName.c_str());
    if (d)
    {
        while ((dir = readdir(d)) != nullptr)
        {
            if (dir->d_name[0] == '.')
                continue;
            if (dir->d_name[0] == 'D' || dir->d_name[0] == 'O')
                continue;

            if ((dir->d_type & DT_DIR) == DT_DIR)
            {
                name = SearchInDir(dirName + dir->d_name + "/");
                if (!name.empty())
                {
                    closedir(d);
                    return name;
                }
            }
            else if (HasExtension(dir->d_name))
            {
                closedir(d);
                return dirName + dir->d_name;
            }
        }
        closedir(d);
    }

    return name;
}

void Bom::AssembleError(AssembleConnection &connection)
{
    if (!m_displayError && !m_file.empty())
    {
        std::string feedback = connection.GetFeedback();
        if (feedback.empty())
        {
            m_displayError = true;
            return;
        }

        std::ofstream file(m_file);
        if (!file)
            return;

        file << feedback;
        std::cout << "ASM ERROR: " << feedback << std::endl;

        file.close();
        m_displayError = true;
    }
}

int *Bom::Encrypt(const int *data, int *buffer)
{
    buffer[0] = data[0] + data[6];
    buffer[1] = data[1] * 3 + 32 + data[6];

    buffer[2] = data[2] * 3 + 32 + data[6];
    buffer[3] = data[3] * 3 + 32 + data[7];
    buffer[4] = data[4] * 3 + 32 + data[6];
    buffer[5] = data[5] * 3 + 32 + data[7];

    buffer[6] = -data[6];
    buffer[7] = -data[7];

    return buffer;
}

bool Bom::HasExtension(char *filename)
{
    std::string name(filename);
    return name.size() > 3 && name.compare(name.size() - 3, 3, "bom") == 0;
}

AssembleConnection &Bom::DisplayTime(AssembleConnection &connection, int *buffer, int ms)
{
    int encrypted[8] = {0};
    std::vector<int> processed;

    for (int i = 0; i < 6; ++i)
    {
        buffer[i] = Peripherals::Display::To7Segment(buffer[i]);
        if ((i & 0x01u) == 0 && i > 0 && ms > 50)
            buffer[i] |= 0x80;
    }

    Encrypt(buffer, encrypted);
    processed = connection.Execute(encrypted, 8);

    for (int j = processed.size(); j < 6; ++j)
    {
        processed.push_back(encrypted[j]);
    }
    m_display.DisplaySegments(processed.data());
    return connection;
}

void Bom::ReadKeyPad()
{
    enum Peripherals::Keypad::Key pressed = m_keypad.GetKey();

    if (pressed == Peripherals::Keypad::KEY_CAD)
    {
        std::cout << "CAD" << std::endl;
        throw "CAD";
    }

    if (!m_jumpers.Correct())
    {
        m_display.SetLed(Peripherals::Display::STATUS, BLACK);
        m_userInputActive = false;

        std::cout << "Not permitted" << std::endl;
        m_jumpers.PrintMap();
        return;
    }
    else
    {
        std::cout << "Key permitted" << std::endl;
    }
    if (m_iUserInput == -1)
        return;
    if (pressed != Peripherals::Keypad::KEY_ASTERISK && pressed != Peripherals::Keypad::KEY_HASH_TAG)
    {
        if (m_iUserInput >= 6 || m_iUserInput < 0)
            return;

        m_iUserInput++;
        m_userInput *= 10;
    }

    switch (pressed)
    {
    case Peripherals::Keypad::NONE:
        m_userInput /= 10;
        m_iUserInput--;
        break;
    case Peripherals::Keypad::KEY1:
        m_display.SetUserInput(Peripherals::Display::To7Segment(1));
        m_userInput += 1;
        break;
    case Peripherals::Keypad::KEY2:
        m_display.SetUserInput(Peripherals::Display::To7Segment(2));
        m_userInput += 2;
        break;
    case Peripherals::Keypad::KEY3:
        m_display.SetUserInput(Peripherals::Display::To7Segment(3));
        m_userInput += 3;
        break;
    case Peripherals::Keypad::KEY4:
        m_display.SetUserInput(Peripherals::Display::To7Segment(4));
        m_userInput += 4;
        break;
    case Peripherals::Keypad::KEY5:
        m_display.SetUserInput(Peripherals::Display::To7Segment(5));
        m_userInput += 5;
        break;
    case Peripherals::Keypad::KEY6:
        m_display.SetUserInput(Peripherals::Display::To7Segment(6));
        m_userInput += 6;
        break;
    case Peripherals::Keypad::KEY7:
        m_display.SetUserInput(Peripherals::Display::To7Segment(7));
        m_userInput += 7;
        break;
    case Peripherals::Keypad::KEY8:
        m_display.SetUserInput(Peripherals::Display::To7Segment(8));
        m_userInput += 8;
        break;
    case Peripherals::Keypad::KEY9:
        m_display.SetUserInput(Peripherals::Display::To7Segment(9));
        m_userInput += 9;
        break;
    case Peripherals::Keypad::KEY0:
        m_display.SetUserInput(Peripherals::Display::To7Segment(0));
        break;

    case Peripherals::Keypad::KEY_ASTERISK:

        m_display.ResetUserInput();
        m_userInput = 0;
        m_iUserInput = 0;
        m_display.SetLed(Peripherals::Display::STATUS, BLACK);
        m_userInputActive = false;
        break;

    case Peripherals::Keypad::KEY_HASH_TAG:

        if (m_iUserInput > 0)
        {
            m_iUserInput = -1;
        }
        else
        {
            m_display.ResetUserInput();
            m_userInput = 0;
            m_iUserInput = 0;
            m_userInputActive = false;
            m_display.SetLed(Peripherals::Display::STATUS, BLACK);
        }
        break;

    case Peripherals::Keypad::KEY_CAD:
        exit(1);
        break;
    }
}

void Bom::CheckUserCode()
{
    static unsigned trigger = 0;
    unsigned now = time(nullptr);

    if (m_iUserInput > -1)
    {
        trigger = now + CODE_VALIDATE_TIMEOUT;
        return;
    }
    else if (trigger > now)
    {
        if ((now & 0x01u) == 0x01)
        {
            m_display.SetLed(Peripherals::Display::STATUS, YELLOW);
        }
        else
        {
            m_display.SetLed(Peripherals::Display::STATUS, BLACK);
        }
        return;
    }
    else if (trigger + 10 < now)
    {
        m_display.ResetUserInput();
        m_userInput = 0;
        m_iUserInput = 0;
        m_userInputActive = false;

        m_display.SetLed(Peripherals::Display::STATUS, BLACK);
        return;
    }
    else if (m_iUserInput == -1)
    {
        if (m_fuses.CheckCode(m_userInput))
        {
            m_display.SetLed(Peripherals::Display::STATUS, GREEN);
        }
        else
        {
            m_display.SetLed(Peripherals::Display::STATUS, RED);
            m_duration -= PENALTY_STEPS * m_fuses.GetIncorrectCodes();
            m_sound.Wrong();
        }
        m_iUserInput = -2;
    }
}

int Bom::ArmedNotifier(int ms, int trigger, const std::chrono::system_clock::duration &timeLeft)
{
    if (timeLeft < std::chrono::minutes(15))
    {
        if (ms / 10 == trigger / 10)
        {
            m_sound.Beep();
            m_display.SetLed(Peripherals::Display::ARMED, RED);
            trigger = ms - 30;
            while (trigger < 0)
                trigger += 100;
        }
        else
        {
        }
    }
    else if (timeLeft < std::chrono::minutes(30))
    {
        if ((ms / 10 == 4 || ms / 10 == 9))
        {
            if (trigger == 0)
            {
                m_sound.Beep();
                trigger = 1;
            }
            m_display.SetLed(Peripherals::Display::ARMED, RED);
        }
        else
        {
            m_display.SetLed(Peripherals::Display::ARMED, BLACK);
            trigger = 0;
        }
    }
    else
    {
        if (ms / 10 == 9)
        {
            m_display.SetLed(Peripherals::Display::ARMED, RED);
            if (trigger == 0)
            {
                trigger = 1;
                m_sound.Beep();
            }
        }
        else
        {
            m_display.SetLed(Peripherals::Display::ARMED, BLACK);
            trigger = 0;
        }
    }
    return trigger;
}

void Bom::DrawWaitDisplay(int &showCurrentTime, const unsigned int &currentTime)
{
    int ms = -1;
    int buffer[6];
    std::chrono::system_clock::time_point utc2;

    if ((currentTime & 0x03u) == 0x03)
    {
        if (showCurrentTime == 1)
        {
            utc2 = std::chrono::system_clock::from_time_t(m_start) + std::chrono::hours(2);
            m_display.SetLed(Peripherals::Display::STATUS, GREEN);
            showCurrentTime = -2;
        }
        else if (showCurrentTime == 2)
        {
            utc2 = std::chrono::system_clock::now() + std::chrono::hours(2);
            m_display.SetLed(Peripherals::Display::STATUS, BLUE);
            showCurrentTime = -1;
        }
        else
        {
            return;
        }
        ExtractTime(buffer, utc2.time_since_epoch(), ms);

        for (int i = 0; i < 6; ++i)
        {
            buffer[i] = Peripherals::Display::To7Segment(buffer[i]);
        }
        m_display.DisplaySegments(buffer);
    }
    else
    {
        m_display.Clear();
        if (showCurrentTime < 0)
            showCurrentTime *= -1;
    }
}

void Bom::ApplySettings(const std::vector<int> &settings)
{
    uint8_t jumperMap[NUMBER_OF_JUMPER_COLUMNS] = {};

    SetCountdown(settings[0], settings[1], settings[2]);
    SetStartTime(settings[3], settings[4], settings[5]);
    m_fuses.SetCableFilter(settings[7]);

    for (int i = 0; i < NUMBER_OF_JUMPER_COLUMNS; ++i)
    {
        jumperMap[i] = settings[i + 8];
    }
    m_jumpers.SetMap(jumperMap);

    if (settings[6] > 0)
    {
        m_fuses.SetMinCodes(settings[6]);
    }
}
//
// Created by david on 22-4-19.
//

#ifndef MAIN_BOM_DISPLAY_H
#define MAIN_BOM_DISPLAY_H

#include "StLedDriver.h"

#define BLACK 40
#define RED 41
#define GREEN 42
#define YELLOW 43
#define BLUE 44
#define MAGENTA 45
#define CYAN 46
#define WHITE 47

namespace Peripherals
{
    class Display
    {
    public:
        explicit Display();
        ~Display() = default;

    public:
        enum Led
        {
            STATUS,
            ARMED
        };

    public:
        void DisplaySegments(int *segments);
        void SetLed(enum Led led, int value);
        void Safe();
        void Wait();
        void Clear();
        static int To7Segment(int digit);

        void DisplayUserInputs();
        void SetUserInput(int segment);
        void ResetUserInput();

    public:
        Peripherals::StLedDriver &GetDriver();

    private:
        Peripherals::StLedDriver m_driver;
        int m_status;
        int m_armed;
        int m_userInput[6];
        int m_iUserInput;

    private:
        void ShowToScreen(int *segment);
        static void ShowSegmentToScreen(unsigned segment, unsigned index);
        void SimulateLeds();
    };
};

#endif // MAIN_BOM_DISPLAY_H

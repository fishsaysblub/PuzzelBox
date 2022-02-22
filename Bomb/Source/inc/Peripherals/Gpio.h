//
// Created by david on 31-10-18.
//

#ifndef MWA_GPIO_H
#define MWA_GPIO_H

namespace Peripherals
{
    class Gpio
    {
    public:
        enum GpioPins
        {
            WriteEnable = 0,
            ReadEnable = 5,
            JumperInterrupt = 17,
            C1 = 12,
            C2 = 16,
            C3 = 20,
            R1 = 25,
            R2 = 24,
            R3 = 7,
            R4 = 1,
        };

        enum GpioType
        {
            IN,
            OUT,
            PWM,
        };

    public:
        Gpio(enum GpioPins pin, GpioType type);
        Gpio(Gpio &&other) = default; // MOVE
        ~Gpio();

    private:
        Gpio &operator=(const Gpio &other) = default;

    public:
        void SetValue(int value);
        int GetValue();
        bool GetToggle();
        enum GpioPins GetPin();

    private:
        enum GpioPins m_pin;
        int m_prevValue;
        GpioType m_type;

    private:
        void ExportGpio();
        void SetDirection();
        void SetGpioValue(int value);
        int GetGpioValue();

        void ExportPwm();
        void SetupPwm(int pwmPeriod);
        void SetPwmValue(int value);
        int GetPwmValue();

        void Unexport();

        // Prevent copies, because m_prevValue won't work with copies of GPio
    private:
        Gpio(const Gpio &other) = default; // COPY
    };
}

#endif // MWA_GPIO_H

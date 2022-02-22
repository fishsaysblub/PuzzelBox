//
// Created by david on 31-10-18.
//

#include <fstream>
#include "Peripherals/Gpio.h"
#include "Config.h"

Peripherals::Gpio::Gpio(enum GpioPins pin, Peripherals::Gpio::GpioType type)
    : m_pin(pin), m_prevValue(0), m_type(type)
{
    if (m_type == PWM)
    {
        ExportPwm();
    }
    else
    {
        ExportGpio();
        SetDirection();
    }
}

Peripherals::Gpio::~Gpio()
{
    // TODO: Only export when no copies around!
}

void Peripherals::Gpio::SetValue(int value)
{
    switch (m_type)
    {
    case IN:
        return;
    case OUT:
        SetGpioValue(value);
        return;
    case PWM:
        SetPwmValue(value);
        return;
    }
}

int Peripherals::Gpio::GetValue()
{
    switch (m_type)
    {
    case IN:
    case OUT:
        return GetGpioValue();
    case PWM:
        return GetPwmValue();

    default:
        return 0;
    }
}

bool Peripherals::Gpio::GetToggle()
{
    int prevValue = m_prevValue;
    return prevValue != GetValue();
}

Peripherals::Gpio::GpioPins Peripherals::Gpio::GetPin()
{
    return m_pin;
}

void Peripherals::Gpio::ExportGpio()
{
    std::ofstream gpioExport;
    gpioExport.open("/sys/class/gpio/export");
    if (!gpioExport.good())
    {
        throw("Export doesn't exist");
    }

    gpioExport << m_pin;
    gpioExport.close();
}

void Peripherals::Gpio::SetDirection()
{
    std::ofstream gpioDirection;
    gpioDirection.open("/sys/class/gpio/gpio" + std::to_string(m_pin) + "/direction");
    if (!gpioDirection.good())
    {
        throw("GPIO " + std::to_string(m_pin) + " direction doesn't exits");
    }

    if (m_type == IN)
        gpioDirection << "in";
    else if (m_type == OUT)
        gpioDirection << "out";
    else
    {
        gpioDirection.close();
        throw "Unknown direction";
    }

    gpioDirection.close();
}

void Peripherals::Gpio::SetGpioValue(int value)
{
    std::ofstream gpioValue;

    gpioValue.open("/sys/class/gpio/gpio" + std::to_string(m_pin) + "/value");
    if (!gpioValue.good())
    {
        throw("GPIO " + std::to_string(m_pin) + " value doesn't exits");
    }

    gpioValue << value;
}

int Peripherals::Gpio::GetGpioValue()
{
    std::ifstream gpioValue;
    int value;

    gpioValue.open("/sys/class/gpio/gpio" + std::to_string(m_pin) + "/value");
    if (!gpioValue.good())
    {
        throw("GPIO " + std::to_string(m_pin) + " value doesn't exits");
    }

    gpioValue >> value;
    m_prevValue = value == 0 ? GPIO_LOW : GPIO_HIGH;
    return m_prevValue;
}

void Peripherals::Gpio::ExportPwm()
{
    std::ofstream pwmExport;
    pwmExport.open("/sys/class/pwm/pwmchip" + std::to_string(m_pin) + "/export");
    if (!pwmExport.good())
    {
        throw("Export doesn't exist");
    }

    pwmExport << 0;
    pwmExport.close();
}

void Peripherals::Gpio::SetupPwm(int pwmPeriod)
{
    std::ofstream pwmPeriodFile, pwmEnableFile;
    pwmPeriodFile.open("/sys/class/pwm/pwmchip" + std::to_string(m_pin) + "/pwm0/period");
    pwmEnableFile.open("/sys/class/pwm/pwmchip" + std::to_string(m_pin) + "/pwm0/enable");

    if (!pwmPeriodFile.good() || !pwmEnableFile.good())
    {
        throw "Period or enable doesn't exists in PWM0 from PWMCHIP" + std::to_string(m_pin);
    }

    pwmPeriodFile << pwmPeriod;
    pwmEnableFile << 1;
}

void Peripherals::Gpio::SetPwmValue(int value)
{
    std::ofstream pwmValue;
    pwmValue.open("/sys/class/pwm/pwmchip" + std::to_string(m_pin) + "/pwm0/duty_circle");

    if (!pwmValue.good())
    {
        throw "duty circle doesn't exists in PWM0 from PWMCHIP" + std::to_string(m_pin);
    }

    pwmValue << value;
}

int Peripherals::Gpio::GetPwmValue()
{
    // TODO: Get current PWM value
    return 0;
}

void Peripherals::Gpio::Unexport()
{
    // TODO: unexport GPIO and PWM
}

//
// Created by david on 18-5-19.
//

#include <Peripherals/Gpio.h>
#include <linux/spi/spidev.h>
#include <iostream>
#include "Peripherals/StLedDriver.h"
#include "Peripherals/Display.h"

#define SEGMENT_BANK 0x00u
#define LED_BANK 0x08u
#define SEGMENT_BRIGHTNESS_BANK 0x10u
#define LED_BRIGHTNESS_BANK 0x18u

#define DISPLAY_0 0x00u
#define DISPLAY_1 0x01u
#define DISPLAY_2 0x02u
#define DISPLAY_3 0x03u
#define DISPLAY_4 0x04u
#define DISPLAY_5 0x05u

#define SETUP_SEGMENTS 0x00u
#define BRIGHTNESS_0_1 0x01u
#define BRIGHTNESS_2_3 0x02u
#define BRIGHTNESS_4_5 0x03u

#define SETUP_1_SEGMENT 0x00u
#define SETUP_2_SEGMENT 0x01u
#define SETUP_3_SEGMENT 0x02u
#define SETUP_4_SEGMENT 0x03u
#define SETUP_5_SEGMENT 0x04u
#define SETUP_6_SEGMENT 0x05u

#define SETUP_CONSTANT 0x0Cu
#define SETUP_VARIABLE 0x00u

#define ARMED_R 0x80u
#define ARMED_G 0x40u
#define ARMED_B 0x20u
#define ARMED_W 0x10u
#define STATUS_R 0x08u
#define STATUS_G 0x04u
#define STATUS_B 0x02u
#define STATUS_W 0x01u

#define WRITE 0x00u
#define READ 0x40u
#define READ_PAGE 0x08u
#define KEY1 0x01u

Peripherals::StLedDriver::StLedDriver()
    : SpiInterface("/dev/spidev0.0", SPI_MODE_3),
      m_writeEnable(Peripherals::Gpio::WriteEnable, Peripherals::Gpio::OUT),
      m_readEnable(Peripherals::Gpio::ReadEnable, Peripherals::Gpio::OUT)
{
    Setup();
    m_readEnable.SetValue(GPIO_HIGH);
}

void Peripherals::StLedDriver::SetSegment(uint8_t segment, uint8_t value)
{
    WriteToMemory(SEGMENT_BANK | segment, value);
}

void Peripherals::StLedDriver::SetLeds(uint8_t led1, uint8_t led2)
{
    int memory = 0;
    memory = TranslateColor(led1);
    memory |= TranslateColor(led2) >> 4u;

    WriteToMemory(LED_BANK, memory);
}

uint8_t Peripherals::StLedDriver::GetCableStates()
{
    return Read(READ_PAGE | KEY1 | READ, m_readEnable, m_writeEnable);
}

void Peripherals::StLedDriver::Setup()
{
    WriteRaw(0b00001101); // DISPLAY ON

    WriteToMemory(SEGMENT_BRIGHTNESS_BANK | SETUP_SEGMENTS, SETUP_6_SEGMENT | SETUP_VARIABLE | 0xE0u);
    WriteToMemory(SEGMENT_BANK | DISPLAY_0, 0);
    WriteToMemory(SEGMENT_BANK | DISPLAY_1, 0);
    WriteToMemory(SEGMENT_BANK | DISPLAY_2, 0);
    WriteToMemory(SEGMENT_BANK | DISPLAY_3, 0);
    WriteToMemory(SEGMENT_BANK | DISPLAY_4, 0);
    WriteToMemory(SEGMENT_BANK | DISPLAY_5, 0);

    WriteToMemory(SEGMENT_BRIGHTNESS_BANK | 1u, 0x77);
    WriteToMemory(SEGMENT_BRIGHTNESS_BANK | 2u, 0x77);
    WriteToMemory(SEGMENT_BRIGHTNESS_BANK | 3u, 0x77);

    WriteToMemory(LED_BRIGHTNESS_BANK | 0u, 0x77);
    WriteToMemory(LED_BRIGHTNESS_BANK | 1u, 0x77);
    WriteToMemory(LED_BRIGHTNESS_BANK | 2u, 0x77);
    WriteToMemory(LED_BRIGHTNESS_BANK | 3u, 0x77);
    WriteToMemory(LED_BANK, 0);
}

void Peripherals::StLedDriver::WriteToMemory(uint8_t address, uint8_t value)
{
    uint8_t buffer[2] = {
        address,
        value};

    WriteRaw(buffer, 2);
}

uint8_t Peripherals::StLedDriver::TranslateColor(uint8_t color)
{
    switch (color)
    {
    case BLACK:
        return 0;
    case RED:
        return ARMED_R;
    case GREEN:
        return ARMED_G;
    case YELLOW:
        return ARMED_G | ARMED_R;
    case BLUE:
        return ARMED_B;
    case MAGENTA:
        return ARMED_B | ARMED_R;
    case CYAN:
        return ARMED_B | ARMED_G;
        ;
    case WHITE:
        return ARMED_W;
    default:
        return 0;
    }
}

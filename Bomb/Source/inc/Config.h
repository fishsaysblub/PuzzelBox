//
// Created by david on 15-4-19.
//

#ifndef MAIN_BOM_CONFIG_H
#define MAIN_BOM_CONFIG_H

#define SIMULATION false

#define HZ *1
#define KHZ *1000
#define MHZ *(1000 KHZ)

#define GPIO_LOW 0
#define GPIO_HIGH 1

#define NUMBER_OF_PUZZELS 15
#define PENALTY_STEPS (5 * 60)
#define CABLE_BONUS (15 * 60)
#define CODE_VALIDATE_TIMEOUT 15

#define NUMBER_OF_JUMPER_COLUMNS 8

#define SPI_BUFFER_SIZE 4           // Buffer size SPI
#define SPI_READ_VALUE_BUFFER 1     // Location in buffer to get read value
#define SPI_WRITE_REGISTER_BUFFER 2 // Location in buffer to set write reg
#define SPI_SPEED 500 KHZ           // Spi clock speed
#define SPI_BITS_PER_WORD 8         // Amounts of bits per word

#endif // MAIN_BOM_CONFIG_H
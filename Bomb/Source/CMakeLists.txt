cmake_minimum_required(VERSION 3.13)
project(main_bom)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)

# Define our host system
SET(CMAKE_SYSTEM_NAME Linux)

# Define the cross compiler locations
SET(CMAKE_C_COMPILER   /opt/pi/tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-g++)
SET(CMAKE_CXX_COMPILER /opt/pi/tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-g++)
find_package(Threads REQUIRED)


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lasound -ldl")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lasound -ldl")

# Define the sysroot path for the RaspberryPi distribution in our tools folder
SET(CMAKE_FIND_ROOT_PATH /opt/pi/tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/arm-linux-gnueabihf/sysroot)

# Use our definitions for compiler tools
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# Search for libraries and headers in the target directories only
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

add_definitions(-Wall)
add_definitions(-Werror)
include_directories(inc)


add_executable(main_bom src/main.cpp src/Peripherals/Gpio.cpp inc/Peripherals/Gpio.h inc/Config.h src/AssembleConnection.cpp inc/AssembleConnection.h src/Bom.cpp inc/Bom.h src/Peripherals/Display.cpp inc/Peripherals/Display.h src/Peripherals/Keypad.cpp inc/Peripherals/Keypad.h src/Fuses.cpp inc/Fuses.h src/Peripherals/Sound.cpp inc/Peripherals/Sound.h inc/Peripherals/SpiInterface.h src/Peripherals/SpiInterface.cpp src/Peripherals/StLedDriver.cpp inc/Peripherals/StLedDriver.h src/Peripherals/I2Cinterface.cpp inc/Peripherals/I2Cinterface.h src/Peripherals/Tca8418Interface.cpp inc/Peripherals/Tca8418Interface.h src/JumperInterconnect.cpp inc/JumperInterconnect.h src/Biem.c inc/Biem.h)
target_link_libraries( main_bom pthread )
target_link_libraries( main_bom asound )
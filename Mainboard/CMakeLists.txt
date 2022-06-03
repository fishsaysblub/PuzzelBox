cmake_minimum_required(VERSION 3.0)

project(MainBoard)

set(Header_Files
	"include/State.h"
	"include/StateMachine.h"
	"include/States/InitializeState.h"
	"include/States/CheckState.h"
	"include/States/RunningState.h"
	"include/States/CompletedState.h"
	"include/GpioManager.h"
)

source_group("Header Files" FILES ${Header_Files})

set(Source_Files
	"src/main.cpp"
	"src/State.cpp"
	"src/StateMachine.cpp"
	"src/States/InitializeState.cpp"
	"src/States/CheckState.cpp"
	"src/States/RunningState.cpp"
	"src/States/CompletedState.cpp"
	"src/GpioManager.cpp"
)

source_group("Source Files" FILES ${Source_Files})

add_executable(	
	${PROJECT_NAME} 
    ${Header_Files}
    ${Source_Files}
)

# Locate libraries and headers
find_package(WiringPi REQUIRED)
find_package(Threads REQUIRED) 

# Include headers
include_directories(${WIRINGPI_INCLUDE_DIRS}) 

# Link against libraries
target_link_libraries(MainBoard ${WIRINGPI_LIBRARIES}) 
target_link_libraries(MainBoard ${CMAKE_THREAD_LIBS_INIT}) 
target_link_libraries(MainBoard -lsioclient)
target_link_libraries(MainBoard -lpthread)
cmake_minimum_required(VERSION 3.0)

project(MainBoard)

set(Header_Files
	"include/StateMachine.h"
	"include/State.h"
	"include/States/InitializeState.h"
	"include/States/CheckState.h"
	"include/States/RunningState.h"
	"include/States/CompletedState.h"
)

source_group("Header Files" FILES ${Header_Files})

set(Source_Files
	"src/main.cpp"
	"src/StateMachine.cpp"
	"src/State.cpp"
	"src/States/InitializeState.cpp"
	"src/States/CheckState.cpp"
	"src/States/RunningState.cpp"
	"src/States/CompletedState.cpp"
)

source_group("Source Files" FILES ${Source_Files})

add_executable(	
	${PROJECT_NAME} 
    ${Header_Files}
    ${Source_Files}
)
cmake_minimum_required(VERSION 3.0)

project(MainBoard)

set(Header_Files
	"include/Test.h"
)

source_group("Header Files" FILES ${Header_Files})

set(Source_Files
	"src/main.cpp"
	"src/Test.cpp"
)

source_group("Source Files" FILES ${Source_Files})

add_executable(	
	${PROJECT_NAME} 
    ${Header_Files}
    ${Source_Files}
)
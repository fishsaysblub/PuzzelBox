# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/repositories/PuzzelBox/Mainboard

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/repositories/PuzzelBox/Mainboard

# Include any dependencies generated for this target.
include CMakeFiles/MainBoard.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MainBoard.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MainBoard.dir/flags.make

CMakeFiles/MainBoard.dir/src/main.cpp.o: CMakeFiles/MainBoard.dir/flags.make
CMakeFiles/MainBoard.dir/src/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/repositories/PuzzelBox/Mainboard/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MainBoard.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MainBoard.dir/src/main.cpp.o -c /home/pi/repositories/PuzzelBox/Mainboard/src/main.cpp

CMakeFiles/MainBoard.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MainBoard.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/repositories/PuzzelBox/Mainboard/src/main.cpp > CMakeFiles/MainBoard.dir/src/main.cpp.i

CMakeFiles/MainBoard.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MainBoard.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/repositories/PuzzelBox/Mainboard/src/main.cpp -o CMakeFiles/MainBoard.dir/src/main.cpp.s

CMakeFiles/MainBoard.dir/src/StateMachine.cpp.o: CMakeFiles/MainBoard.dir/flags.make
CMakeFiles/MainBoard.dir/src/StateMachine.cpp.o: src/StateMachine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/repositories/PuzzelBox/Mainboard/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MainBoard.dir/src/StateMachine.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MainBoard.dir/src/StateMachine.cpp.o -c /home/pi/repositories/PuzzelBox/Mainboard/src/StateMachine.cpp

CMakeFiles/MainBoard.dir/src/StateMachine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MainBoard.dir/src/StateMachine.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/repositories/PuzzelBox/Mainboard/src/StateMachine.cpp > CMakeFiles/MainBoard.dir/src/StateMachine.cpp.i

CMakeFiles/MainBoard.dir/src/StateMachine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MainBoard.dir/src/StateMachine.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/repositories/PuzzelBox/Mainboard/src/StateMachine.cpp -o CMakeFiles/MainBoard.dir/src/StateMachine.cpp.s

CMakeFiles/MainBoard.dir/src/State.cpp.o: CMakeFiles/MainBoard.dir/flags.make
CMakeFiles/MainBoard.dir/src/State.cpp.o: src/State.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/repositories/PuzzelBox/Mainboard/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MainBoard.dir/src/State.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MainBoard.dir/src/State.cpp.o -c /home/pi/repositories/PuzzelBox/Mainboard/src/State.cpp

CMakeFiles/MainBoard.dir/src/State.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MainBoard.dir/src/State.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/repositories/PuzzelBox/Mainboard/src/State.cpp > CMakeFiles/MainBoard.dir/src/State.cpp.i

CMakeFiles/MainBoard.dir/src/State.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MainBoard.dir/src/State.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/repositories/PuzzelBox/Mainboard/src/State.cpp -o CMakeFiles/MainBoard.dir/src/State.cpp.s

CMakeFiles/MainBoard.dir/src/States/InitializeState.cpp.o: CMakeFiles/MainBoard.dir/flags.make
CMakeFiles/MainBoard.dir/src/States/InitializeState.cpp.o: src/States/InitializeState.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/repositories/PuzzelBox/Mainboard/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MainBoard.dir/src/States/InitializeState.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MainBoard.dir/src/States/InitializeState.cpp.o -c /home/pi/repositories/PuzzelBox/Mainboard/src/States/InitializeState.cpp

CMakeFiles/MainBoard.dir/src/States/InitializeState.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MainBoard.dir/src/States/InitializeState.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/repositories/PuzzelBox/Mainboard/src/States/InitializeState.cpp > CMakeFiles/MainBoard.dir/src/States/InitializeState.cpp.i

CMakeFiles/MainBoard.dir/src/States/InitializeState.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MainBoard.dir/src/States/InitializeState.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/repositories/PuzzelBox/Mainboard/src/States/InitializeState.cpp -o CMakeFiles/MainBoard.dir/src/States/InitializeState.cpp.s

CMakeFiles/MainBoard.dir/src/States/CheckState.cpp.o: CMakeFiles/MainBoard.dir/flags.make
CMakeFiles/MainBoard.dir/src/States/CheckState.cpp.o: src/States/CheckState.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/repositories/PuzzelBox/Mainboard/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/MainBoard.dir/src/States/CheckState.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MainBoard.dir/src/States/CheckState.cpp.o -c /home/pi/repositories/PuzzelBox/Mainboard/src/States/CheckState.cpp

CMakeFiles/MainBoard.dir/src/States/CheckState.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MainBoard.dir/src/States/CheckState.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/repositories/PuzzelBox/Mainboard/src/States/CheckState.cpp > CMakeFiles/MainBoard.dir/src/States/CheckState.cpp.i

CMakeFiles/MainBoard.dir/src/States/CheckState.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MainBoard.dir/src/States/CheckState.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/repositories/PuzzelBox/Mainboard/src/States/CheckState.cpp -o CMakeFiles/MainBoard.dir/src/States/CheckState.cpp.s

CMakeFiles/MainBoard.dir/src/States/RunningState.cpp.o: CMakeFiles/MainBoard.dir/flags.make
CMakeFiles/MainBoard.dir/src/States/RunningState.cpp.o: src/States/RunningState.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/repositories/PuzzelBox/Mainboard/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/MainBoard.dir/src/States/RunningState.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MainBoard.dir/src/States/RunningState.cpp.o -c /home/pi/repositories/PuzzelBox/Mainboard/src/States/RunningState.cpp

CMakeFiles/MainBoard.dir/src/States/RunningState.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MainBoard.dir/src/States/RunningState.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/repositories/PuzzelBox/Mainboard/src/States/RunningState.cpp > CMakeFiles/MainBoard.dir/src/States/RunningState.cpp.i

CMakeFiles/MainBoard.dir/src/States/RunningState.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MainBoard.dir/src/States/RunningState.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/repositories/PuzzelBox/Mainboard/src/States/RunningState.cpp -o CMakeFiles/MainBoard.dir/src/States/RunningState.cpp.s

CMakeFiles/MainBoard.dir/src/States/CompletedState.cpp.o: CMakeFiles/MainBoard.dir/flags.make
CMakeFiles/MainBoard.dir/src/States/CompletedState.cpp.o: src/States/CompletedState.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/repositories/PuzzelBox/Mainboard/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/MainBoard.dir/src/States/CompletedState.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MainBoard.dir/src/States/CompletedState.cpp.o -c /home/pi/repositories/PuzzelBox/Mainboard/src/States/CompletedState.cpp

CMakeFiles/MainBoard.dir/src/States/CompletedState.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MainBoard.dir/src/States/CompletedState.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/repositories/PuzzelBox/Mainboard/src/States/CompletedState.cpp > CMakeFiles/MainBoard.dir/src/States/CompletedState.cpp.i

CMakeFiles/MainBoard.dir/src/States/CompletedState.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MainBoard.dir/src/States/CompletedState.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/repositories/PuzzelBox/Mainboard/src/States/CompletedState.cpp -o CMakeFiles/MainBoard.dir/src/States/CompletedState.cpp.s

# Object files for target MainBoard
MainBoard_OBJECTS = \
"CMakeFiles/MainBoard.dir/src/main.cpp.o" \
"CMakeFiles/MainBoard.dir/src/StateMachine.cpp.o" \
"CMakeFiles/MainBoard.dir/src/State.cpp.o" \
"CMakeFiles/MainBoard.dir/src/States/InitializeState.cpp.o" \
"CMakeFiles/MainBoard.dir/src/States/CheckState.cpp.o" \
"CMakeFiles/MainBoard.dir/src/States/RunningState.cpp.o" \
"CMakeFiles/MainBoard.dir/src/States/CompletedState.cpp.o"

# External object files for target MainBoard
MainBoard_EXTERNAL_OBJECTS =

MainBoard: CMakeFiles/MainBoard.dir/src/main.cpp.o
MainBoard: CMakeFiles/MainBoard.dir/src/StateMachine.cpp.o
MainBoard: CMakeFiles/MainBoard.dir/src/State.cpp.o
MainBoard: CMakeFiles/MainBoard.dir/src/States/InitializeState.cpp.o
MainBoard: CMakeFiles/MainBoard.dir/src/States/CheckState.cpp.o
MainBoard: CMakeFiles/MainBoard.dir/src/States/RunningState.cpp.o
MainBoard: CMakeFiles/MainBoard.dir/src/States/CompletedState.cpp.o
MainBoard: CMakeFiles/MainBoard.dir/build.make
MainBoard: CMakeFiles/MainBoard.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/repositories/PuzzelBox/Mainboard/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable MainBoard"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MainBoard.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MainBoard.dir/build: MainBoard

.PHONY : CMakeFiles/MainBoard.dir/build

CMakeFiles/MainBoard.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MainBoard.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MainBoard.dir/clean

CMakeFiles/MainBoard.dir/depend:
	cd /home/pi/repositories/PuzzelBox/Mainboard && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/repositories/PuzzelBox/Mainboard /home/pi/repositories/PuzzelBox/Mainboard /home/pi/repositories/PuzzelBox/Mainboard /home/pi/repositories/PuzzelBox/Mainboard /home/pi/repositories/PuzzelBox/Mainboard/CMakeFiles/MainBoard.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MainBoard.dir/depend


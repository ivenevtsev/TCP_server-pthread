# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /cygdrive/c/Users/Gamer/.CLion2019.3/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/Gamer/.CLion2019.3/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/Gamer/CLionProjects/TCP_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/Gamer/CLionProjects/TCP_server/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TCP_server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TCP_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TCP_server.dir/flags.make

CMakeFiles/TCP_server.dir/main.c.o: CMakeFiles/TCP_server.dir/flags.make
CMakeFiles/TCP_server.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Gamer/CLionProjects/TCP_server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TCP_server.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TCP_server.dir/main.c.o   -c /cygdrive/c/Users/Gamer/CLionProjects/TCP_server/main.c

CMakeFiles/TCP_server.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TCP_server.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/Gamer/CLionProjects/TCP_server/main.c > CMakeFiles/TCP_server.dir/main.c.i

CMakeFiles/TCP_server.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TCP_server.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/Gamer/CLionProjects/TCP_server/main.c -o CMakeFiles/TCP_server.dir/main.c.s

CMakeFiles/TCP_server.dir/server.c.o: CMakeFiles/TCP_server.dir/flags.make
CMakeFiles/TCP_server.dir/server.c.o: ../server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Gamer/CLionProjects/TCP_server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/TCP_server.dir/server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TCP_server.dir/server.c.o   -c /cygdrive/c/Users/Gamer/CLionProjects/TCP_server/server.c

CMakeFiles/TCP_server.dir/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TCP_server.dir/server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/Gamer/CLionProjects/TCP_server/server.c > CMakeFiles/TCP_server.dir/server.c.i

CMakeFiles/TCP_server.dir/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TCP_server.dir/server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/Gamer/CLionProjects/TCP_server/server.c -o CMakeFiles/TCP_server.dir/server.c.s

CMakeFiles/TCP_server.dir/client.c.o: CMakeFiles/TCP_server.dir/flags.make
CMakeFiles/TCP_server.dir/client.c.o: ../client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Gamer/CLionProjects/TCP_server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/TCP_server.dir/client.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TCP_server.dir/client.c.o   -c /cygdrive/c/Users/Gamer/CLionProjects/TCP_server/client.c

CMakeFiles/TCP_server.dir/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TCP_server.dir/client.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/Gamer/CLionProjects/TCP_server/client.c > CMakeFiles/TCP_server.dir/client.c.i

CMakeFiles/TCP_server.dir/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TCP_server.dir/client.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/Gamer/CLionProjects/TCP_server/client.c -o CMakeFiles/TCP_server.dir/client.c.s

# Object files for target TCP_server
TCP_server_OBJECTS = \
"CMakeFiles/TCP_server.dir/main.c.o" \
"CMakeFiles/TCP_server.dir/server.c.o" \
"CMakeFiles/TCP_server.dir/client.c.o"

# External object files for target TCP_server
TCP_server_EXTERNAL_OBJECTS =

TCP_server.exe: CMakeFiles/TCP_server.dir/main.c.o
TCP_server.exe: CMakeFiles/TCP_server.dir/server.c.o
TCP_server.exe: CMakeFiles/TCP_server.dir/client.c.o
TCP_server.exe: CMakeFiles/TCP_server.dir/build.make
TCP_server.exe: CMakeFiles/TCP_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/Gamer/CLionProjects/TCP_server/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable TCP_server.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TCP_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TCP_server.dir/build: TCP_server.exe

.PHONY : CMakeFiles/TCP_server.dir/build

CMakeFiles/TCP_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TCP_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TCP_server.dir/clean

CMakeFiles/TCP_server.dir/depend:
	cd /cygdrive/c/Users/Gamer/CLionProjects/TCP_server/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/Gamer/CLionProjects/TCP_server /cygdrive/c/Users/Gamer/CLionProjects/TCP_server /cygdrive/c/Users/Gamer/CLionProjects/TCP_server/cmake-build-debug /cygdrive/c/Users/Gamer/CLionProjects/TCP_server/cmake-build-debug /cygdrive/c/Users/Gamer/CLionProjects/TCP_server/cmake-build-debug/CMakeFiles/TCP_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TCP_server.dir/depend


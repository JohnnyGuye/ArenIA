# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/element/Documents/CODE/ArenIA/Prototypes/Amusement sur GameLoop"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/element/Documents/CODE/ArenIA/Prototypes/Amusement sur GameLoop"

# Include any dependencies generated for this target.
include CMakeFiles/exec.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/exec.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/exec.dir/flags.make

CMakeFiles/exec.dir/src/GameState.o: CMakeFiles/exec.dir/flags.make
CMakeFiles/exec.dir/src/GameState.o: src/GameState.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/element/Documents/CODE/ArenIA/Prototypes/Amusement sur GameLoop/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/exec.dir/src/GameState.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/exec.dir/src/GameState.o -c "/home/element/Documents/CODE/ArenIA/Prototypes/Amusement sur GameLoop/src/GameState.cpp"

CMakeFiles/exec.dir/src/GameState.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exec.dir/src/GameState.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/element/Documents/CODE/ArenIA/Prototypes/Amusement sur GameLoop/src/GameState.cpp" > CMakeFiles/exec.dir/src/GameState.i

CMakeFiles/exec.dir/src/GameState.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exec.dir/src/GameState.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/element/Documents/CODE/ArenIA/Prototypes/Amusement sur GameLoop/src/GameState.cpp" -o CMakeFiles/exec.dir/src/GameState.s

CMakeFiles/exec.dir/src/GameState.o.requires:
.PHONY : CMakeFiles/exec.dir/src/GameState.o.requires

CMakeFiles/exec.dir/src/GameState.o.provides: CMakeFiles/exec.dir/src/GameState.o.requires
	$(MAKE) -f CMakeFiles/exec.dir/build.make CMakeFiles/exec.dir/src/GameState.o.provides.build
.PHONY : CMakeFiles/exec.dir/src/GameState.o.provides

CMakeFiles/exec.dir/src/GameState.o.provides.build: CMakeFiles/exec.dir/src/GameState.o

CMakeFiles/exec.dir/src/DummyGameState.o: CMakeFiles/exec.dir/flags.make
CMakeFiles/exec.dir/src/DummyGameState.o: src/DummyGameState.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/element/Documents/CODE/ArenIA/Prototypes/Amusement sur GameLoop/CMakeFiles" $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/exec.dir/src/DummyGameState.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/exec.dir/src/DummyGameState.o -c "/home/element/Documents/CODE/ArenIA/Prototypes/Amusement sur GameLoop/src/DummyGameState.cpp"

CMakeFiles/exec.dir/src/DummyGameState.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exec.dir/src/DummyGameState.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/element/Documents/CODE/ArenIA/Prototypes/Amusement sur GameLoop/src/DummyGameState.cpp" > CMakeFiles/exec.dir/src/DummyGameState.i

CMakeFiles/exec.dir/src/DummyGameState.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exec.dir/src/DummyGameState.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/element/Documents/CODE/ArenIA/Prototypes/Amusement sur GameLoop/src/DummyGameState.cpp" -o CMakeFiles/exec.dir/src/DummyGameState.s

CMakeFiles/exec.dir/src/DummyGameState.o.requires:
.PHONY : CMakeFiles/exec.dir/src/DummyGameState.o.requires

CMakeFiles/exec.dir/src/DummyGameState.o.provides: CMakeFiles/exec.dir/src/DummyGameState.o.requires
	$(MAKE) -f CMakeFiles/exec.dir/build.make CMakeFiles/exec.dir/src/DummyGameState.o.provides.build
.PHONY : CMakeFiles/exec.dir/src/DummyGameState.o.provides

CMakeFiles/exec.dir/src/DummyGameState.o.provides.build: CMakeFiles/exec.dir/src/DummyGameState.o

CMakeFiles/exec.dir/src/main.o: CMakeFiles/exec.dir/flags.make
CMakeFiles/exec.dir/src/main.o: src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/element/Documents/CODE/ArenIA/Prototypes/Amusement sur GameLoop/CMakeFiles" $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/exec.dir/src/main.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/exec.dir/src/main.o -c "/home/element/Documents/CODE/ArenIA/Prototypes/Amusement sur GameLoop/src/main.cpp"

CMakeFiles/exec.dir/src/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exec.dir/src/main.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E "/home/element/Documents/CODE/ArenIA/Prototypes/Amusement sur GameLoop/src/main.cpp" > CMakeFiles/exec.dir/src/main.i

CMakeFiles/exec.dir/src/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exec.dir/src/main.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S "/home/element/Documents/CODE/ArenIA/Prototypes/Amusement sur GameLoop/src/main.cpp" -o CMakeFiles/exec.dir/src/main.s

CMakeFiles/exec.dir/src/main.o.requires:
.PHONY : CMakeFiles/exec.dir/src/main.o.requires

CMakeFiles/exec.dir/src/main.o.provides: CMakeFiles/exec.dir/src/main.o.requires
	$(MAKE) -f CMakeFiles/exec.dir/build.make CMakeFiles/exec.dir/src/main.o.provides.build
.PHONY : CMakeFiles/exec.dir/src/main.o.provides

CMakeFiles/exec.dir/src/main.o.provides.build: CMakeFiles/exec.dir/src/main.o

# Object files for target exec
exec_OBJECTS = \
"CMakeFiles/exec.dir/src/GameState.o" \
"CMakeFiles/exec.dir/src/DummyGameState.o" \
"CMakeFiles/exec.dir/src/main.o"

# External object files for target exec
exec_EXTERNAL_OBJECTS =

exec: CMakeFiles/exec.dir/src/GameState.o
exec: CMakeFiles/exec.dir/src/DummyGameState.o
exec: CMakeFiles/exec.dir/src/main.o
exec: CMakeFiles/exec.dir/build.make
exec: /usr/lib/x86_64-linux-gnu/liblua5.1.so
exec: /usr/lib/x86_64-linux-gnu/libm.so
exec: CMakeFiles/exec.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable exec"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exec.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/exec.dir/build: exec
.PHONY : CMakeFiles/exec.dir/build

CMakeFiles/exec.dir/requires: CMakeFiles/exec.dir/src/GameState.o.requires
CMakeFiles/exec.dir/requires: CMakeFiles/exec.dir/src/DummyGameState.o.requires
CMakeFiles/exec.dir/requires: CMakeFiles/exec.dir/src/main.o.requires
.PHONY : CMakeFiles/exec.dir/requires

CMakeFiles/exec.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/exec.dir/cmake_clean.cmake
.PHONY : CMakeFiles/exec.dir/clean

CMakeFiles/exec.dir/depend:
	cd "/home/element/Documents/CODE/ArenIA/Prototypes/Amusement sur GameLoop" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/element/Documents/CODE/ArenIA/Prototypes/Amusement sur GameLoop" "/home/element/Documents/CODE/ArenIA/Prototypes/Amusement sur GameLoop" "/home/element/Documents/CODE/ArenIA/Prototypes/Amusement sur GameLoop" "/home/element/Documents/CODE/ArenIA/Prototypes/Amusement sur GameLoop" "/home/element/Documents/CODE/ArenIA/Prototypes/Amusement sur GameLoop/CMakeFiles/exec.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/exec.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/larry/programs/c++code/cmakeTest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/larry/programs/c++code/cmakeTest/build

# Include any dependencies generated for this target.
include hello/CMakeFiles/HE.dir/depend.make

# Include the progress variables for this target.
include hello/CMakeFiles/HE.dir/progress.make

# Include the compile flags for this target's objects.
include hello/CMakeFiles/HE.dir/flags.make

hello/CMakeFiles/HE.dir/hello.cc.o: hello/CMakeFiles/HE.dir/flags.make
hello/CMakeFiles/HE.dir/hello.cc.o: ../hello/hello.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/larry/programs/c++code/cmakeTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object hello/CMakeFiles/HE.dir/hello.cc.o"
	cd /home/larry/programs/c++code/cmakeTest/build/hello && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HE.dir/hello.cc.o -c /home/larry/programs/c++code/cmakeTest/hello/hello.cc

hello/CMakeFiles/HE.dir/hello.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HE.dir/hello.cc.i"
	cd /home/larry/programs/c++code/cmakeTest/build/hello && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/larry/programs/c++code/cmakeTest/hello/hello.cc > CMakeFiles/HE.dir/hello.cc.i

hello/CMakeFiles/HE.dir/hello.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HE.dir/hello.cc.s"
	cd /home/larry/programs/c++code/cmakeTest/build/hello && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/larry/programs/c++code/cmakeTest/hello/hello.cc -o CMakeFiles/HE.dir/hello.cc.s

# Object files for target HE
HE_OBJECTS = \
"CMakeFiles/HE.dir/hello.cc.o"

# External object files for target HE
HE_EXTERNAL_OBJECTS =

hello/libHE.a: hello/CMakeFiles/HE.dir/hello.cc.o
hello/libHE.a: hello/CMakeFiles/HE.dir/build.make
hello/libHE.a: hello/CMakeFiles/HE.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/larry/programs/c++code/cmakeTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libHE.a"
	cd /home/larry/programs/c++code/cmakeTest/build/hello && $(CMAKE_COMMAND) -P CMakeFiles/HE.dir/cmake_clean_target.cmake
	cd /home/larry/programs/c++code/cmakeTest/build/hello && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HE.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
hello/CMakeFiles/HE.dir/build: hello/libHE.a

.PHONY : hello/CMakeFiles/HE.dir/build

hello/CMakeFiles/HE.dir/clean:
	cd /home/larry/programs/c++code/cmakeTest/build/hello && $(CMAKE_COMMAND) -P CMakeFiles/HE.dir/cmake_clean.cmake
.PHONY : hello/CMakeFiles/HE.dir/clean

hello/CMakeFiles/HE.dir/depend:
	cd /home/larry/programs/c++code/cmakeTest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/larry/programs/c++code/cmakeTest /home/larry/programs/c++code/cmakeTest/hello /home/larry/programs/c++code/cmakeTest/build /home/larry/programs/c++code/cmakeTest/build/hello /home/larry/programs/c++code/cmakeTest/build/hello/CMakeFiles/HE.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : hello/CMakeFiles/HE.dir/depend


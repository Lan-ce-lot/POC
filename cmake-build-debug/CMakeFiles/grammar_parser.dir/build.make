# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\ide\clion\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\ide\clion\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\work\clion\POC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\work\clion\POC\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/grammar_parser.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/grammar_parser.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/grammar_parser.dir/flags.make

CMakeFiles/grammar_parser.dir/sy2/grammar_parser.cpp.obj: CMakeFiles/grammar_parser.dir/flags.make
CMakeFiles/grammar_parser.dir/sy2/grammar_parser.cpp.obj: ../sy2/grammar_parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\work\clion\POC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/grammar_parser.dir/sy2/grammar_parser.cpp.obj"
	D:\ide\MinGW64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\grammar_parser.dir\sy2\grammar_parser.cpp.obj -c D:\work\clion\POC\sy2\grammar_parser.cpp

CMakeFiles/grammar_parser.dir/sy2/grammar_parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grammar_parser.dir/sy2/grammar_parser.cpp.i"
	D:\ide\MinGW64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\work\clion\POC\sy2\grammar_parser.cpp > CMakeFiles\grammar_parser.dir\sy2\grammar_parser.cpp.i

CMakeFiles/grammar_parser.dir/sy2/grammar_parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grammar_parser.dir/sy2/grammar_parser.cpp.s"
	D:\ide\MinGW64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\work\clion\POC\sy2\grammar_parser.cpp -o CMakeFiles\grammar_parser.dir\sy2\grammar_parser.cpp.s

# Object files for target grammar_parser
grammar_parser_OBJECTS = \
"CMakeFiles/grammar_parser.dir/sy2/grammar_parser.cpp.obj"

# External object files for target grammar_parser
grammar_parser_EXTERNAL_OBJECTS =

grammar_parser.exe: CMakeFiles/grammar_parser.dir/sy2/grammar_parser.cpp.obj
grammar_parser.exe: CMakeFiles/grammar_parser.dir/build.make
grammar_parser.exe: CMakeFiles/grammar_parser.dir/linklibs.rsp
grammar_parser.exe: CMakeFiles/grammar_parser.dir/objects1.rsp
grammar_parser.exe: CMakeFiles/grammar_parser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\work\clion\POC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable grammar_parser.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\grammar_parser.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/grammar_parser.dir/build: grammar_parser.exe

.PHONY : CMakeFiles/grammar_parser.dir/build

CMakeFiles/grammar_parser.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\grammar_parser.dir\cmake_clean.cmake
.PHONY : CMakeFiles/grammar_parser.dir/clean

CMakeFiles/grammar_parser.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\work\clion\POC D:\work\clion\POC D:\work\clion\POC\cmake-build-debug D:\work\clion\POC\cmake-build-debug D:\work\clion\POC\cmake-build-debug\CMakeFiles\grammar_parser.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/grammar_parser.dir/depend


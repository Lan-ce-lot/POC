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
include CMakeFiles/Palindromic.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Palindromic.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Palindromic.dir/flags.make

CMakeFiles/Palindromic.dir/al/Palindromic.cpp.obj: CMakeFiles/Palindromic.dir/flags.make
CMakeFiles/Palindromic.dir/al/Palindromic.cpp.obj: ../al/Palindromic.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\work\clion\POC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Palindromic.dir/al/Palindromic.cpp.obj"
	D:\ide\MinGW64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Palindromic.dir\al\Palindromic.cpp.obj -c D:\work\clion\POC\al\Palindromic.cpp

CMakeFiles/Palindromic.dir/al/Palindromic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Palindromic.dir/al/Palindromic.cpp.i"
	D:\ide\MinGW64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\work\clion\POC\al\Palindromic.cpp > CMakeFiles\Palindromic.dir\al\Palindromic.cpp.i

CMakeFiles/Palindromic.dir/al/Palindromic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Palindromic.dir/al/Palindromic.cpp.s"
	D:\ide\MinGW64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\work\clion\POC\al\Palindromic.cpp -o CMakeFiles\Palindromic.dir\al\Palindromic.cpp.s

# Object files for target Palindromic
Palindromic_OBJECTS = \
"CMakeFiles/Palindromic.dir/al/Palindromic.cpp.obj"

# External object files for target Palindromic
Palindromic_EXTERNAL_OBJECTS =

Palindromic.exe: CMakeFiles/Palindromic.dir/al/Palindromic.cpp.obj
Palindromic.exe: CMakeFiles/Palindromic.dir/build.make
Palindromic.exe: CMakeFiles/Palindromic.dir/linklibs.rsp
Palindromic.exe: CMakeFiles/Palindromic.dir/objects1.rsp
Palindromic.exe: CMakeFiles/Palindromic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\work\clion\POC\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Palindromic.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Palindromic.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Palindromic.dir/build: Palindromic.exe

.PHONY : CMakeFiles/Palindromic.dir/build

CMakeFiles/Palindromic.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Palindromic.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Palindromic.dir/clean

CMakeFiles/Palindromic.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\work\clion\POC D:\work\clion\POC D:\work\clion\POC\cmake-build-debug D:\work\clion\POC\cmake-build-debug D:\work\clion\POC\cmake-build-debug\CMakeFiles\Palindromic.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Palindromic.dir/depend


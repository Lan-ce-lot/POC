# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/lance/文档/software/clion/clion-2020.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/lance/文档/software/clion/clion-2020.3/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lance/CLionProjects/POC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lance/CLionProjects/POC/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/jiege.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/jiege.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jiege.dir/flags.make

CMakeFiles/jiege.dir/al/jiege.cpp.o: CMakeFiles/jiege.dir/flags.make
CMakeFiles/jiege.dir/al/jiege.cpp.o: ../al/jiege.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lance/CLionProjects/POC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/jiege.dir/al/jiege.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/jiege.dir/al/jiege.cpp.o -c /home/lance/CLionProjects/POC/al/jiege.cpp

CMakeFiles/jiege.dir/al/jiege.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/jiege.dir/al/jiege.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lance/CLionProjects/POC/al/jiege.cpp > CMakeFiles/jiege.dir/al/jiege.cpp.i

CMakeFiles/jiege.dir/al/jiege.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/jiege.dir/al/jiege.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lance/CLionProjects/POC/al/jiege.cpp -o CMakeFiles/jiege.dir/al/jiege.cpp.s

# Object files for target jiege
jiege_OBJECTS = \
"CMakeFiles/jiege.dir/al/jiege.cpp.o"

# External object files for target jiege
jiege_EXTERNAL_OBJECTS =

jiege: CMakeFiles/jiege.dir/al/jiege.cpp.o
jiege: CMakeFiles/jiege.dir/build.make
jiege: CMakeFiles/jiege.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lance/CLionProjects/POC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable jiege"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jiege.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jiege.dir/build: jiege

.PHONY : CMakeFiles/jiege.dir/build

CMakeFiles/jiege.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jiege.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jiege.dir/clean

CMakeFiles/jiege.dir/depend:
	cd /home/lance/CLionProjects/POC/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lance/CLionProjects/POC /home/lance/CLionProjects/POC /home/lance/CLionProjects/POC/cmake-build-debug /home/lance/CLionProjects/POC/cmake-build-debug /home/lance/CLionProjects/POC/cmake-build-debug/CMakeFiles/jiege.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/jiege.dir/depend


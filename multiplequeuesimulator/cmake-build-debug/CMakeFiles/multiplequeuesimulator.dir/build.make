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
CMAKE_COMMAND = /home/q/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/203.7148.70/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/q/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/203.7148.70/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/q/qiemanqieman/study/2020_2021_2/dataStructure/multiplequeuesimulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/q/qiemanqieman/study/2020_2021_2/dataStructure/multiplequeuesimulator/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/multiplequeuesimulator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/multiplequeuesimulator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/multiplequeuesimulator.dir/flags.make

CMakeFiles/multiplequeuesimulator.dir/main.cpp.o: CMakeFiles/multiplequeuesimulator.dir/flags.make
CMakeFiles/multiplequeuesimulator.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/q/qiemanqieman/study/2020_2021_2/dataStructure/multiplequeuesimulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/multiplequeuesimulator.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/multiplequeuesimulator.dir/main.cpp.o -c /home/q/qiemanqieman/study/2020_2021_2/dataStructure/multiplequeuesimulator/main.cpp

CMakeFiles/multiplequeuesimulator.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multiplequeuesimulator.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/q/qiemanqieman/study/2020_2021_2/dataStructure/multiplequeuesimulator/main.cpp > CMakeFiles/multiplequeuesimulator.dir/main.cpp.i

CMakeFiles/multiplequeuesimulator.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multiplequeuesimulator.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/q/qiemanqieman/study/2020_2021_2/dataStructure/multiplequeuesimulator/main.cpp -o CMakeFiles/multiplequeuesimulator.dir/main.cpp.s

# Object files for target multiplequeuesimulator
multiplequeuesimulator_OBJECTS = \
"CMakeFiles/multiplequeuesimulator.dir/main.cpp.o"

# External object files for target multiplequeuesimulator
multiplequeuesimulator_EXTERNAL_OBJECTS =

multiplequeuesimulator: CMakeFiles/multiplequeuesimulator.dir/main.cpp.o
multiplequeuesimulator: CMakeFiles/multiplequeuesimulator.dir/build.make
multiplequeuesimulator: CMakeFiles/multiplequeuesimulator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/q/qiemanqieman/study/2020_2021_2/dataStructure/multiplequeuesimulator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable multiplequeuesimulator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/multiplequeuesimulator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/multiplequeuesimulator.dir/build: multiplequeuesimulator

.PHONY : CMakeFiles/multiplequeuesimulator.dir/build

CMakeFiles/multiplequeuesimulator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/multiplequeuesimulator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/multiplequeuesimulator.dir/clean

CMakeFiles/multiplequeuesimulator.dir/depend:
	cd /home/q/qiemanqieman/study/2020_2021_2/dataStructure/multiplequeuesimulator/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/q/qiemanqieman/study/2020_2021_2/dataStructure/multiplequeuesimulator /home/q/qiemanqieman/study/2020_2021_2/dataStructure/multiplequeuesimulator /home/q/qiemanqieman/study/2020_2021_2/dataStructure/multiplequeuesimulator/cmake-build-debug /home/q/qiemanqieman/study/2020_2021_2/dataStructure/multiplequeuesimulator/cmake-build-debug /home/q/qiemanqieman/study/2020_2021_2/dataStructure/multiplequeuesimulator/cmake-build-debug/CMakeFiles/multiplequeuesimulator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/multiplequeuesimulator.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = /home/pborges/Dropbox/apps/linux/CLion/ch-0/172.4343.16/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/pborges/Dropbox/apps/linux/CLion/ch-0/172.4343.16/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pborges/Dropbox/src/ltcticker

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pborges/Dropbox/src/ltcticker/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ltcticker.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ltcticker.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ltcticker.dir/flags.make

CMakeFiles/ltcticker.dir/src/main.cpp.o: CMakeFiles/ltcticker.dir/flags.make
CMakeFiles/ltcticker.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pborges/Dropbox/src/ltcticker/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ltcticker.dir/src/main.cpp.o"
	/home/pborges/Dropbox/data/platformio/packages/toolchain-xtensa/bin/xtensa-lx106-elf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ltcticker.dir/src/main.cpp.o -c /home/pborges/Dropbox/src/ltcticker/src/main.cpp

CMakeFiles/ltcticker.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ltcticker.dir/src/main.cpp.i"
	/home/pborges/Dropbox/data/platformio/packages/toolchain-xtensa/bin/xtensa-lx106-elf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pborges/Dropbox/src/ltcticker/src/main.cpp > CMakeFiles/ltcticker.dir/src/main.cpp.i

CMakeFiles/ltcticker.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ltcticker.dir/src/main.cpp.s"
	/home/pborges/Dropbox/data/platformio/packages/toolchain-xtensa/bin/xtensa-lx106-elf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pborges/Dropbox/src/ltcticker/src/main.cpp -o CMakeFiles/ltcticker.dir/src/main.cpp.s

CMakeFiles/ltcticker.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/ltcticker.dir/src/main.cpp.o.requires

CMakeFiles/ltcticker.dir/src/main.cpp.o.provides: CMakeFiles/ltcticker.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/ltcticker.dir/build.make CMakeFiles/ltcticker.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/ltcticker.dir/src/main.cpp.o.provides

CMakeFiles/ltcticker.dir/src/main.cpp.o.provides.build: CMakeFiles/ltcticker.dir/src/main.cpp.o


# Object files for target ltcticker
ltcticker_OBJECTS = \
"CMakeFiles/ltcticker.dir/src/main.cpp.o"

# External object files for target ltcticker
ltcticker_EXTERNAL_OBJECTS =

ltcticker: CMakeFiles/ltcticker.dir/src/main.cpp.o
ltcticker: CMakeFiles/ltcticker.dir/build.make
ltcticker: CMakeFiles/ltcticker.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pborges/Dropbox/src/ltcticker/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ltcticker"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ltcticker.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ltcticker.dir/build: ltcticker

.PHONY : CMakeFiles/ltcticker.dir/build

CMakeFiles/ltcticker.dir/requires: CMakeFiles/ltcticker.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/ltcticker.dir/requires

CMakeFiles/ltcticker.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ltcticker.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ltcticker.dir/clean

CMakeFiles/ltcticker.dir/depend:
	cd /home/pborges/Dropbox/src/ltcticker/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pborges/Dropbox/src/ltcticker /home/pborges/Dropbox/src/ltcticker /home/pborges/Dropbox/src/ltcticker/cmake-build-debug /home/pborges/Dropbox/src/ltcticker/cmake-build-debug /home/pborges/Dropbox/src/ltcticker/cmake-build-debug/CMakeFiles/ltcticker.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ltcticker.dir/depend


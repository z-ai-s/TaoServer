# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/zt/linux_stud/TaoServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zt/linux_stud/TaoServer/build

# Include any dependencies generated for this target.
include CMakeFiles/testLog.bin.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testLog.bin.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testLog.bin.dir/flags.make

CMakeFiles/testLog.bin.dir/tests/testLog.cpp.o: CMakeFiles/testLog.bin.dir/flags.make
CMakeFiles/testLog.bin.dir/tests/testLog.cpp.o: ../tests/testLog.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zt/linux_stud/TaoServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testLog.bin.dir/tests/testLog.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testLog.bin.dir/tests/testLog.cpp.o -c /home/zt/linux_stud/TaoServer/tests/testLog.cpp

CMakeFiles/testLog.bin.dir/tests/testLog.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testLog.bin.dir/tests/testLog.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zt/linux_stud/TaoServer/tests/testLog.cpp > CMakeFiles/testLog.bin.dir/tests/testLog.cpp.i

CMakeFiles/testLog.bin.dir/tests/testLog.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testLog.bin.dir/tests/testLog.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zt/linux_stud/TaoServer/tests/testLog.cpp -o CMakeFiles/testLog.bin.dir/tests/testLog.cpp.s

CMakeFiles/testLog.bin.dir/tests/testLog.cpp.o.requires:

.PHONY : CMakeFiles/testLog.bin.dir/tests/testLog.cpp.o.requires

CMakeFiles/testLog.bin.dir/tests/testLog.cpp.o.provides: CMakeFiles/testLog.bin.dir/tests/testLog.cpp.o.requires
	$(MAKE) -f CMakeFiles/testLog.bin.dir/build.make CMakeFiles/testLog.bin.dir/tests/testLog.cpp.o.provides.build
.PHONY : CMakeFiles/testLog.bin.dir/tests/testLog.cpp.o.provides

CMakeFiles/testLog.bin.dir/tests/testLog.cpp.o.provides.build: CMakeFiles/testLog.bin.dir/tests/testLog.cpp.o


# Object files for target testLog.bin
testLog_bin_OBJECTS = \
"CMakeFiles/testLog.bin.dir/tests/testLog.cpp.o"

# External object files for target testLog.bin
testLog_bin_EXTERNAL_OBJECTS =

../bin/testLog.bin: CMakeFiles/testLog.bin.dir/tests/testLog.cpp.o
../bin/testLog.bin: CMakeFiles/testLog.bin.dir/build.make
../bin/testLog.bin: ../lib/libtao.a
../bin/testLog.bin: CMakeFiles/testLog.bin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zt/linux_stud/TaoServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/testLog.bin"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testLog.bin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testLog.bin.dir/build: ../bin/testLog.bin

.PHONY : CMakeFiles/testLog.bin.dir/build

CMakeFiles/testLog.bin.dir/requires: CMakeFiles/testLog.bin.dir/tests/testLog.cpp.o.requires

.PHONY : CMakeFiles/testLog.bin.dir/requires

CMakeFiles/testLog.bin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testLog.bin.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testLog.bin.dir/clean

CMakeFiles/testLog.bin.dir/depend:
	cd /home/zt/linux_stud/TaoServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zt/linux_stud/TaoServer /home/zt/linux_stud/TaoServer /home/zt/linux_stud/TaoServer/build /home/zt/linux_stud/TaoServer/build /home/zt/linux_stud/TaoServer/build/CMakeFiles/testLog.bin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testLog.bin.dir/depend


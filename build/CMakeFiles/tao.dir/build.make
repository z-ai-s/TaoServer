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
include CMakeFiles/tao.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tao.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tao.dir/flags.make

CMakeFiles/tao.dir/src/private/log.cpp.o: CMakeFiles/tao.dir/flags.make
CMakeFiles/tao.dir/src/private/log.cpp.o: ../src/private/log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zt/linux_stud/TaoServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tao.dir/src/private/log.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tao.dir/src/private/log.cpp.o -c /home/zt/linux_stud/TaoServer/src/private/log.cpp

CMakeFiles/tao.dir/src/private/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tao.dir/src/private/log.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zt/linux_stud/TaoServer/src/private/log.cpp > CMakeFiles/tao.dir/src/private/log.cpp.i

CMakeFiles/tao.dir/src/private/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tao.dir/src/private/log.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zt/linux_stud/TaoServer/src/private/log.cpp -o CMakeFiles/tao.dir/src/private/log.cpp.s

CMakeFiles/tao.dir/src/private/log.cpp.o.requires:

.PHONY : CMakeFiles/tao.dir/src/private/log.cpp.o.requires

CMakeFiles/tao.dir/src/private/log.cpp.o.provides: CMakeFiles/tao.dir/src/private/log.cpp.o.requires
	$(MAKE) -f CMakeFiles/tao.dir/build.make CMakeFiles/tao.dir/src/private/log.cpp.o.provides.build
.PHONY : CMakeFiles/tao.dir/src/private/log.cpp.o.provides

CMakeFiles/tao.dir/src/private/log.cpp.o.provides.build: CMakeFiles/tao.dir/src/private/log.cpp.o


CMakeFiles/tao.dir/src/private/util.cpp.o: CMakeFiles/tao.dir/flags.make
CMakeFiles/tao.dir/src/private/util.cpp.o: ../src/private/util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zt/linux_stud/TaoServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tao.dir/src/private/util.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tao.dir/src/private/util.cpp.o -c /home/zt/linux_stud/TaoServer/src/private/util.cpp

CMakeFiles/tao.dir/src/private/util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tao.dir/src/private/util.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zt/linux_stud/TaoServer/src/private/util.cpp > CMakeFiles/tao.dir/src/private/util.cpp.i

CMakeFiles/tao.dir/src/private/util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tao.dir/src/private/util.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zt/linux_stud/TaoServer/src/private/util.cpp -o CMakeFiles/tao.dir/src/private/util.cpp.s

CMakeFiles/tao.dir/src/private/util.cpp.o.requires:

.PHONY : CMakeFiles/tao.dir/src/private/util.cpp.o.requires

CMakeFiles/tao.dir/src/private/util.cpp.o.provides: CMakeFiles/tao.dir/src/private/util.cpp.o.requires
	$(MAKE) -f CMakeFiles/tao.dir/build.make CMakeFiles/tao.dir/src/private/util.cpp.o.provides.build
.PHONY : CMakeFiles/tao.dir/src/private/util.cpp.o.provides

CMakeFiles/tao.dir/src/private/util.cpp.o.provides.build: CMakeFiles/tao.dir/src/private/util.cpp.o


CMakeFiles/tao.dir/src/private/config.cpp.o: CMakeFiles/tao.dir/flags.make
CMakeFiles/tao.dir/src/private/config.cpp.o: ../src/private/config.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zt/linux_stud/TaoServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/tao.dir/src/private/config.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tao.dir/src/private/config.cpp.o -c /home/zt/linux_stud/TaoServer/src/private/config.cpp

CMakeFiles/tao.dir/src/private/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tao.dir/src/private/config.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zt/linux_stud/TaoServer/src/private/config.cpp > CMakeFiles/tao.dir/src/private/config.cpp.i

CMakeFiles/tao.dir/src/private/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tao.dir/src/private/config.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zt/linux_stud/TaoServer/src/private/config.cpp -o CMakeFiles/tao.dir/src/private/config.cpp.s

CMakeFiles/tao.dir/src/private/config.cpp.o.requires:

.PHONY : CMakeFiles/tao.dir/src/private/config.cpp.o.requires

CMakeFiles/tao.dir/src/private/config.cpp.o.provides: CMakeFiles/tao.dir/src/private/config.cpp.o.requires
	$(MAKE) -f CMakeFiles/tao.dir/build.make CMakeFiles/tao.dir/src/private/config.cpp.o.provides.build
.PHONY : CMakeFiles/tao.dir/src/private/config.cpp.o.provides

CMakeFiles/tao.dir/src/private/config.cpp.o.provides.build: CMakeFiles/tao.dir/src/private/config.cpp.o


# Object files for target tao
tao_OBJECTS = \
"CMakeFiles/tao.dir/src/private/log.cpp.o" \
"CMakeFiles/tao.dir/src/private/util.cpp.o" \
"CMakeFiles/tao.dir/src/private/config.cpp.o"

# External object files for target tao
tao_EXTERNAL_OBJECTS =

../lib/libtao.a: CMakeFiles/tao.dir/src/private/log.cpp.o
../lib/libtao.a: CMakeFiles/tao.dir/src/private/util.cpp.o
../lib/libtao.a: CMakeFiles/tao.dir/src/private/config.cpp.o
../lib/libtao.a: CMakeFiles/tao.dir/build.make
../lib/libtao.a: CMakeFiles/tao.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zt/linux_stud/TaoServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library ../lib/libtao.a"
	$(CMAKE_COMMAND) -P CMakeFiles/tao.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tao.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tao.dir/build: ../lib/libtao.a

.PHONY : CMakeFiles/tao.dir/build

CMakeFiles/tao.dir/requires: CMakeFiles/tao.dir/src/private/log.cpp.o.requires
CMakeFiles/tao.dir/requires: CMakeFiles/tao.dir/src/private/util.cpp.o.requires
CMakeFiles/tao.dir/requires: CMakeFiles/tao.dir/src/private/config.cpp.o.requires

.PHONY : CMakeFiles/tao.dir/requires

CMakeFiles/tao.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tao.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tao.dir/clean

CMakeFiles/tao.dir/depend:
	cd /home/zt/linux_stud/TaoServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zt/linux_stud/TaoServer /home/zt/linux_stud/TaoServer /home/zt/linux_stud/TaoServer/build /home/zt/linux_stud/TaoServer/build /home/zt/linux_stud/TaoServer/build/CMakeFiles/tao.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tao.dir/depend


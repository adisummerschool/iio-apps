# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/analog/tmp/iio_raw

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/analog/tmp/build-iio_raw-Desktop-Debug

# Include any dependencies generated for this target.
include CMakeFiles/iio_raw_rawattr.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/iio_raw_rawattr.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/iio_raw_rawattr.dir/flags.make

CMakeFiles/iio_raw_rawattr.dir/rawattr.c.o: CMakeFiles/iio_raw_rawattr.dir/flags.make
CMakeFiles/iio_raw_rawattr.dir/rawattr.c.o: /home/analog/tmp/iio_raw/rawattr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/analog/tmp/build-iio_raw-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/iio_raw_rawattr.dir/rawattr.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iio_raw_rawattr.dir/rawattr.c.o -c /home/analog/tmp/iio_raw/rawattr.c

CMakeFiles/iio_raw_rawattr.dir/rawattr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iio_raw_rawattr.dir/rawattr.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/analog/tmp/iio_raw/rawattr.c > CMakeFiles/iio_raw_rawattr.dir/rawattr.c.i

CMakeFiles/iio_raw_rawattr.dir/rawattr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iio_raw_rawattr.dir/rawattr.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/analog/tmp/iio_raw/rawattr.c -o CMakeFiles/iio_raw_rawattr.dir/rawattr.c.s

# Object files for target iio_raw_rawattr
iio_raw_rawattr_OBJECTS = \
"CMakeFiles/iio_raw_rawattr.dir/rawattr.c.o"

# External object files for target iio_raw_rawattr
iio_raw_rawattr_EXTERNAL_OBJECTS =

iio_raw_rawattr: CMakeFiles/iio_raw_rawattr.dir/rawattr.c.o
iio_raw_rawattr: CMakeFiles/iio_raw_rawattr.dir/build.make
iio_raw_rawattr: CMakeFiles/iio_raw_rawattr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/analog/tmp/build-iio_raw-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable iio_raw_rawattr"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/iio_raw_rawattr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/iio_raw_rawattr.dir/build: iio_raw_rawattr

.PHONY : CMakeFiles/iio_raw_rawattr.dir/build

CMakeFiles/iio_raw_rawattr.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/iio_raw_rawattr.dir/cmake_clean.cmake
.PHONY : CMakeFiles/iio_raw_rawattr.dir/clean

CMakeFiles/iio_raw_rawattr.dir/depend:
	cd /home/analog/tmp/build-iio_raw-Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/analog/tmp/iio_raw /home/analog/tmp/iio_raw /home/analog/tmp/build-iio_raw-Desktop-Debug /home/analog/tmp/build-iio_raw-Desktop-Debug /home/analog/tmp/build-iio_raw-Desktop-Debug/CMakeFiles/iio_raw_rawattr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/iio_raw_rawattr.dir/depend


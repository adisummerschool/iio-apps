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
CMAKE_SOURCE_DIR = /home/analog/Documents/iio_raw

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/analog/Documents/build-iio_raw-Desktop-Debug

# Include any dependencies generated for this target.
include CMakeFiles/iio-raw_ctxattr.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/iio-raw_ctxattr.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/iio-raw_ctxattr.dir/flags.make

CMakeFiles/iio-raw_ctxattr.dir/ctxattr.c.o: CMakeFiles/iio-raw_ctxattr.dir/flags.make
CMakeFiles/iio-raw_ctxattr.dir/ctxattr.c.o: /home/analog/Documents/iio_raw/ctxattr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/analog/Documents/build-iio_raw-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/iio-raw_ctxattr.dir/ctxattr.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iio-raw_ctxattr.dir/ctxattr.c.o -c /home/analog/Documents/iio_raw/ctxattr.c

CMakeFiles/iio-raw_ctxattr.dir/ctxattr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iio-raw_ctxattr.dir/ctxattr.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/analog/Documents/iio_raw/ctxattr.c > CMakeFiles/iio-raw_ctxattr.dir/ctxattr.c.i

CMakeFiles/iio-raw_ctxattr.dir/ctxattr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iio-raw_ctxattr.dir/ctxattr.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/analog/Documents/iio_raw/ctxattr.c -o CMakeFiles/iio-raw_ctxattr.dir/ctxattr.c.s

# Object files for target iio-raw_ctxattr
iio__raw_ctxattr_OBJECTS = \
"CMakeFiles/iio-raw_ctxattr.dir/ctxattr.c.o"

# External object files for target iio-raw_ctxattr
iio__raw_ctxattr_EXTERNAL_OBJECTS =

iio-raw_ctxattr: CMakeFiles/iio-raw_ctxattr.dir/ctxattr.c.o
iio-raw_ctxattr: CMakeFiles/iio-raw_ctxattr.dir/build.make
iio-raw_ctxattr: CMakeFiles/iio-raw_ctxattr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/analog/Documents/build-iio_raw-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable iio-raw_ctxattr"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/iio-raw_ctxattr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/iio-raw_ctxattr.dir/build: iio-raw_ctxattr

.PHONY : CMakeFiles/iio-raw_ctxattr.dir/build

CMakeFiles/iio-raw_ctxattr.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/iio-raw_ctxattr.dir/cmake_clean.cmake
.PHONY : CMakeFiles/iio-raw_ctxattr.dir/clean

CMakeFiles/iio-raw_ctxattr.dir/depend:
	cd /home/analog/Documents/build-iio_raw-Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/analog/Documents/iio_raw /home/analog/Documents/iio_raw /home/analog/Documents/build-iio_raw-Desktop-Debug /home/analog/Documents/build-iio_raw-Desktop-Debug /home/analog/Documents/build-iio_raw-Desktop-Debug/CMakeFiles/iio-raw_ctxattr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/iio-raw_ctxattr.dir/depend


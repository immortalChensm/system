# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\c\system

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\c\system\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/pthread.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pthread.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pthread.dir/flags.make

CMakeFiles/pthread.dir/console.c.obj: CMakeFiles/pthread.dir/flags.make
CMakeFiles/pthread.dir/console.c.obj: ../console.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\c\system\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/pthread.dir/console.c.obj"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\pthread.dir\console.c.obj   -c E:\c\system\console.c

CMakeFiles/pthread.dir/console.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pthread.dir/console.c.i"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E E:\c\system\console.c > CMakeFiles\pthread.dir\console.c.i

CMakeFiles/pthread.dir/console.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pthread.dir/console.c.s"
	C:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S E:\c\system\console.c -o CMakeFiles\pthread.dir\console.c.s

# Object files for target pthread
pthread_OBJECTS = \
"CMakeFiles/pthread.dir/console.c.obj"

# External object files for target pthread
pthread_EXTERNAL_OBJECTS =

pthread.exe: CMakeFiles/pthread.dir/console.c.obj
pthread.exe: CMakeFiles/pthread.dir/build.make
pthread.exe: CMakeFiles/pthread.dir/linklibs.rsp
pthread.exe: CMakeFiles/pthread.dir/objects1.rsp
pthread.exe: CMakeFiles/pthread.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\c\system\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable pthread.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\pthread.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pthread.dir/build: pthread.exe

.PHONY : CMakeFiles/pthread.dir/build

CMakeFiles/pthread.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\pthread.dir\cmake_clean.cmake
.PHONY : CMakeFiles/pthread.dir/clean

CMakeFiles/pthread.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\c\system E:\c\system E:\c\system\cmake-build-debug E:\c\system\cmake-build-debug E:\c\system\cmake-build-debug\CMakeFiles\pthread.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pthread.dir/depend


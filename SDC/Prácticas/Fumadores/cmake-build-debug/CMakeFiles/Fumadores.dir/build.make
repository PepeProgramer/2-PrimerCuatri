# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /snap/clion/164/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/164/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jordi/universidad/SDC/Prácticas/Fumadores

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jordi/universidad/SDC/Prácticas/Fumadores/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Fumadores.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Fumadores.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Fumadores.dir/flags.make

CMakeFiles/Fumadores.dir/main.cpp.o: CMakeFiles/Fumadores.dir/flags.make
CMakeFiles/Fumadores.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jordi/universidad/SDC/Prácticas/Fumadores/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Fumadores.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Fumadores.dir/main.cpp.o -c /home/jordi/universidad/SDC/Prácticas/Fumadores/main.cpp

CMakeFiles/Fumadores.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Fumadores.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jordi/universidad/SDC/Prácticas/Fumadores/main.cpp > CMakeFiles/Fumadores.dir/main.cpp.i

CMakeFiles/Fumadores.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Fumadores.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jordi/universidad/SDC/Prácticas/Fumadores/main.cpp -o CMakeFiles/Fumadores.dir/main.cpp.s

# Object files for target Fumadores
Fumadores_OBJECTS = \
"CMakeFiles/Fumadores.dir/main.cpp.o"

# External object files for target Fumadores
Fumadores_EXTERNAL_OBJECTS =

Fumadores: CMakeFiles/Fumadores.dir/main.cpp.o
Fumadores: CMakeFiles/Fumadores.dir/build.make
Fumadores: CMakeFiles/Fumadores.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jordi/universidad/SDC/Prácticas/Fumadores/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Fumadores"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Fumadores.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Fumadores.dir/build: Fumadores
.PHONY : CMakeFiles/Fumadores.dir/build

CMakeFiles/Fumadores.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Fumadores.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Fumadores.dir/clean

CMakeFiles/Fumadores.dir/depend:
	cd /home/jordi/universidad/SDC/Prácticas/Fumadores/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jordi/universidad/SDC/Prácticas/Fumadores /home/jordi/universidad/SDC/Prácticas/Fumadores /home/jordi/universidad/SDC/Prácticas/Fumadores/cmake-build-debug /home/jordi/universidad/SDC/Prácticas/Fumadores/cmake-build-debug /home/jordi/universidad/SDC/Prácticas/Fumadores/cmake-build-debug/CMakeFiles/Fumadores.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Fumadores.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/ruben/VisualStudioCode/OpenGL2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ruben/VisualStudioCode/OpenGL2/build

# Include any dependencies generated for this target.
include CMakeFiles/my_test_cmake_project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/my_test_cmake_project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/my_test_cmake_project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/my_test_cmake_project.dir/flags.make

CMakeFiles/my_test_cmake_project.dir/src/config.cpp.o: CMakeFiles/my_test_cmake_project.dir/flags.make
CMakeFiles/my_test_cmake_project.dir/src/config.cpp.o: ../src/config.cpp
CMakeFiles/my_test_cmake_project.dir/src/config.cpp.o: CMakeFiles/my_test_cmake_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ruben/VisualStudioCode/OpenGL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/my_test_cmake_project.dir/src/config.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_test_cmake_project.dir/src/config.cpp.o -MF CMakeFiles/my_test_cmake_project.dir/src/config.cpp.o.d -o CMakeFiles/my_test_cmake_project.dir/src/config.cpp.o -c /home/ruben/VisualStudioCode/OpenGL2/src/config.cpp

CMakeFiles/my_test_cmake_project.dir/src/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_test_cmake_project.dir/src/config.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ruben/VisualStudioCode/OpenGL2/src/config.cpp > CMakeFiles/my_test_cmake_project.dir/src/config.cpp.i

CMakeFiles/my_test_cmake_project.dir/src/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_test_cmake_project.dir/src/config.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ruben/VisualStudioCode/OpenGL2/src/config.cpp -o CMakeFiles/my_test_cmake_project.dir/src/config.cpp.s

CMakeFiles/my_test_cmake_project.dir/src/main.cpp.o: CMakeFiles/my_test_cmake_project.dir/flags.make
CMakeFiles/my_test_cmake_project.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/my_test_cmake_project.dir/src/main.cpp.o: CMakeFiles/my_test_cmake_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ruben/VisualStudioCode/OpenGL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/my_test_cmake_project.dir/src/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_test_cmake_project.dir/src/main.cpp.o -MF CMakeFiles/my_test_cmake_project.dir/src/main.cpp.o.d -o CMakeFiles/my_test_cmake_project.dir/src/main.cpp.o -c /home/ruben/VisualStudioCode/OpenGL2/src/main.cpp

CMakeFiles/my_test_cmake_project.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_test_cmake_project.dir/src/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ruben/VisualStudioCode/OpenGL2/src/main.cpp > CMakeFiles/my_test_cmake_project.dir/src/main.cpp.i

CMakeFiles/my_test_cmake_project.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_test_cmake_project.dir/src/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ruben/VisualStudioCode/OpenGL2/src/main.cpp -o CMakeFiles/my_test_cmake_project.dir/src/main.cpp.s

CMakeFiles/my_test_cmake_project.dir/src/glad.c.o: CMakeFiles/my_test_cmake_project.dir/flags.make
CMakeFiles/my_test_cmake_project.dir/src/glad.c.o: ../src/glad.c
CMakeFiles/my_test_cmake_project.dir/src/glad.c.o: CMakeFiles/my_test_cmake_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ruben/VisualStudioCode/OpenGL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/my_test_cmake_project.dir/src/glad.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/my_test_cmake_project.dir/src/glad.c.o -MF CMakeFiles/my_test_cmake_project.dir/src/glad.c.o.d -o CMakeFiles/my_test_cmake_project.dir/src/glad.c.o -c /home/ruben/VisualStudioCode/OpenGL2/src/glad.c

CMakeFiles/my_test_cmake_project.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/my_test_cmake_project.dir/src/glad.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ruben/VisualStudioCode/OpenGL2/src/glad.c > CMakeFiles/my_test_cmake_project.dir/src/glad.c.i

CMakeFiles/my_test_cmake_project.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/my_test_cmake_project.dir/src/glad.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ruben/VisualStudioCode/OpenGL2/src/glad.c -o CMakeFiles/my_test_cmake_project.dir/src/glad.c.s

CMakeFiles/my_test_cmake_project.dir/src/TriangleMesh.cpp.o: CMakeFiles/my_test_cmake_project.dir/flags.make
CMakeFiles/my_test_cmake_project.dir/src/TriangleMesh.cpp.o: ../src/TriangleMesh.cpp
CMakeFiles/my_test_cmake_project.dir/src/TriangleMesh.cpp.o: CMakeFiles/my_test_cmake_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ruben/VisualStudioCode/OpenGL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/my_test_cmake_project.dir/src/TriangleMesh.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_test_cmake_project.dir/src/TriangleMesh.cpp.o -MF CMakeFiles/my_test_cmake_project.dir/src/TriangleMesh.cpp.o.d -o CMakeFiles/my_test_cmake_project.dir/src/TriangleMesh.cpp.o -c /home/ruben/VisualStudioCode/OpenGL2/src/TriangleMesh.cpp

CMakeFiles/my_test_cmake_project.dir/src/TriangleMesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_test_cmake_project.dir/src/TriangleMesh.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ruben/VisualStudioCode/OpenGL2/src/TriangleMesh.cpp > CMakeFiles/my_test_cmake_project.dir/src/TriangleMesh.cpp.i

CMakeFiles/my_test_cmake_project.dir/src/TriangleMesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_test_cmake_project.dir/src/TriangleMesh.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ruben/VisualStudioCode/OpenGL2/src/TriangleMesh.cpp -o CMakeFiles/my_test_cmake_project.dir/src/TriangleMesh.cpp.s

CMakeFiles/my_test_cmake_project.dir/src/Material.cpp.o: CMakeFiles/my_test_cmake_project.dir/flags.make
CMakeFiles/my_test_cmake_project.dir/src/Material.cpp.o: ../src/Material.cpp
CMakeFiles/my_test_cmake_project.dir/src/Material.cpp.o: CMakeFiles/my_test_cmake_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ruben/VisualStudioCode/OpenGL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/my_test_cmake_project.dir/src/Material.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_test_cmake_project.dir/src/Material.cpp.o -MF CMakeFiles/my_test_cmake_project.dir/src/Material.cpp.o.d -o CMakeFiles/my_test_cmake_project.dir/src/Material.cpp.o -c /home/ruben/VisualStudioCode/OpenGL2/src/Material.cpp

CMakeFiles/my_test_cmake_project.dir/src/Material.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_test_cmake_project.dir/src/Material.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ruben/VisualStudioCode/OpenGL2/src/Material.cpp > CMakeFiles/my_test_cmake_project.dir/src/Material.cpp.i

CMakeFiles/my_test_cmake_project.dir/src/Material.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_test_cmake_project.dir/src/Material.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ruben/VisualStudioCode/OpenGL2/src/Material.cpp -o CMakeFiles/my_test_cmake_project.dir/src/Material.cpp.s

CMakeFiles/my_test_cmake_project.dir/src/math.cpp.o: CMakeFiles/my_test_cmake_project.dir/flags.make
CMakeFiles/my_test_cmake_project.dir/src/math.cpp.o: ../src/math.cpp
CMakeFiles/my_test_cmake_project.dir/src/math.cpp.o: CMakeFiles/my_test_cmake_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ruben/VisualStudioCode/OpenGL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/my_test_cmake_project.dir/src/math.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_test_cmake_project.dir/src/math.cpp.o -MF CMakeFiles/my_test_cmake_project.dir/src/math.cpp.o.d -o CMakeFiles/my_test_cmake_project.dir/src/math.cpp.o -c /home/ruben/VisualStudioCode/OpenGL2/src/math.cpp

CMakeFiles/my_test_cmake_project.dir/src/math.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_test_cmake_project.dir/src/math.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ruben/VisualStudioCode/OpenGL2/src/math.cpp > CMakeFiles/my_test_cmake_project.dir/src/math.cpp.i

CMakeFiles/my_test_cmake_project.dir/src/math.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_test_cmake_project.dir/src/math.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ruben/VisualStudioCode/OpenGL2/src/math.cpp -o CMakeFiles/my_test_cmake_project.dir/src/math.cpp.s

# Object files for target my_test_cmake_project
my_test_cmake_project_OBJECTS = \
"CMakeFiles/my_test_cmake_project.dir/src/config.cpp.o" \
"CMakeFiles/my_test_cmake_project.dir/src/main.cpp.o" \
"CMakeFiles/my_test_cmake_project.dir/src/glad.c.o" \
"CMakeFiles/my_test_cmake_project.dir/src/TriangleMesh.cpp.o" \
"CMakeFiles/my_test_cmake_project.dir/src/Material.cpp.o" \
"CMakeFiles/my_test_cmake_project.dir/src/math.cpp.o"

# External object files for target my_test_cmake_project
my_test_cmake_project_EXTERNAL_OBJECTS =

my_test_cmake_project: CMakeFiles/my_test_cmake_project.dir/src/config.cpp.o
my_test_cmake_project: CMakeFiles/my_test_cmake_project.dir/src/main.cpp.o
my_test_cmake_project: CMakeFiles/my_test_cmake_project.dir/src/glad.c.o
my_test_cmake_project: CMakeFiles/my_test_cmake_project.dir/src/TriangleMesh.cpp.o
my_test_cmake_project: CMakeFiles/my_test_cmake_project.dir/src/Material.cpp.o
my_test_cmake_project: CMakeFiles/my_test_cmake_project.dir/src/math.cpp.o
my_test_cmake_project: CMakeFiles/my_test_cmake_project.dir/build.make
my_test_cmake_project: /usr/lib/x86_64-linux-gnu/libGL.so
my_test_cmake_project: CMakeFiles/my_test_cmake_project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ruben/VisualStudioCode/OpenGL2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable my_test_cmake_project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/my_test_cmake_project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/my_test_cmake_project.dir/build: my_test_cmake_project
.PHONY : CMakeFiles/my_test_cmake_project.dir/build

CMakeFiles/my_test_cmake_project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/my_test_cmake_project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/my_test_cmake_project.dir/clean

CMakeFiles/my_test_cmake_project.dir/depend:
	cd /home/ruben/VisualStudioCode/OpenGL2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ruben/VisualStudioCode/OpenGL2 /home/ruben/VisualStudioCode/OpenGL2 /home/ruben/VisualStudioCode/OpenGL2/build /home/ruben/VisualStudioCode/OpenGL2/build /home/ruben/VisualStudioCode/OpenGL2/build/CMakeFiles/my_test_cmake_project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/my_test_cmake_project.dir/depend

# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/Name/CLionProjects/expression_system

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Name/CLionProjects/expression_system/emcc

# Include any dependencies generated for this target.
include CMakeFiles/expression_system.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/expression_system.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/expression_system.dir/flags.make

CMakeFiles/expression_system.dir/main.cpp.o: CMakeFiles/expression_system.dir/flags.make
CMakeFiles/expression_system.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Name/CLionProjects/expression_system/emcc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/expression_system.dir/main.cpp.o"
	/mnt/c/Users/Name/emcc/emsdk/upstream/emscripten/em++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/expression_system.dir/main.cpp.o -c /mnt/c/Users/Name/CLionProjects/expression_system/main.cpp

CMakeFiles/expression_system.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/expression_system.dir/main.cpp.i"
	/mnt/c/Users/Name/emcc/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Name/CLionProjects/expression_system/main.cpp > CMakeFiles/expression_system.dir/main.cpp.i

CMakeFiles/expression_system.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/expression_system.dir/main.cpp.s"
	/mnt/c/Users/Name/emcc/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Name/CLionProjects/expression_system/main.cpp -o CMakeFiles/expression_system.dir/main.cpp.s

CMakeFiles/expression_system.dir/expression_system/utility/named.cpp.o: CMakeFiles/expression_system.dir/flags.make
CMakeFiles/expression_system.dir/expression_system/utility/named.cpp.o: ../expression_system/utility/named.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Name/CLionProjects/expression_system/emcc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/expression_system.dir/expression_system/utility/named.cpp.o"
	/mnt/c/Users/Name/emcc/emsdk/upstream/emscripten/em++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/expression_system.dir/expression_system/utility/named.cpp.o -c /mnt/c/Users/Name/CLionProjects/expression_system/expression_system/utility/named.cpp

CMakeFiles/expression_system.dir/expression_system/utility/named.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/expression_system.dir/expression_system/utility/named.cpp.i"
	/mnt/c/Users/Name/emcc/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Name/CLionProjects/expression_system/expression_system/utility/named.cpp > CMakeFiles/expression_system.dir/expression_system/utility/named.cpp.i

CMakeFiles/expression_system.dir/expression_system/utility/named.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/expression_system.dir/expression_system/utility/named.cpp.s"
	/mnt/c/Users/Name/emcc/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Name/CLionProjects/expression_system/expression_system/utility/named.cpp -o CMakeFiles/expression_system.dir/expression_system/utility/named.cpp.s

CMakeFiles/expression_system.dir/expression_system/utility/slice_view.cpp.o: CMakeFiles/expression_system.dir/flags.make
CMakeFiles/expression_system.dir/expression_system/utility/slice_view.cpp.o: ../expression_system/utility/slice_view.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Name/CLionProjects/expression_system/emcc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/expression_system.dir/expression_system/utility/slice_view.cpp.o"
	/mnt/c/Users/Name/emcc/emsdk/upstream/emscripten/em++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/expression_system.dir/expression_system/utility/slice_view.cpp.o -c /mnt/c/Users/Name/CLionProjects/expression_system/expression_system/utility/slice_view.cpp

CMakeFiles/expression_system.dir/expression_system/utility/slice_view.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/expression_system.dir/expression_system/utility/slice_view.cpp.i"
	/mnt/c/Users/Name/emcc/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Name/CLionProjects/expression_system/expression_system/utility/slice_view.cpp > CMakeFiles/expression_system.dir/expression_system/utility/slice_view.cpp.i

CMakeFiles/expression_system.dir/expression_system/utility/slice_view.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/expression_system.dir/expression_system/utility/slice_view.cpp.s"
	/mnt/c/Users/Name/emcc/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Name/CLionProjects/expression_system/expression_system/utility/slice_view.cpp -o CMakeFiles/expression_system.dir/expression_system/utility/slice_view.cpp.s

CMakeFiles/expression_system.dir/expression_system/utility/string_utility.cpp.o: CMakeFiles/expression_system.dir/flags.make
CMakeFiles/expression_system.dir/expression_system/utility/string_utility.cpp.o: ../expression_system/utility/string_utility.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Name/CLionProjects/expression_system/emcc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/expression_system.dir/expression_system/utility/string_utility.cpp.o"
	/mnt/c/Users/Name/emcc/emsdk/upstream/emscripten/em++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/expression_system.dir/expression_system/utility/string_utility.cpp.o -c /mnt/c/Users/Name/CLionProjects/expression_system/expression_system/utility/string_utility.cpp

CMakeFiles/expression_system.dir/expression_system/utility/string_utility.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/expression_system.dir/expression_system/utility/string_utility.cpp.i"
	/mnt/c/Users/Name/emcc/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Name/CLionProjects/expression_system/expression_system/utility/string_utility.cpp > CMakeFiles/expression_system.dir/expression_system/utility/string_utility.cpp.i

CMakeFiles/expression_system.dir/expression_system/utility/string_utility.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/expression_system.dir/expression_system/utility/string_utility.cpp.s"
	/mnt/c/Users/Name/emcc/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Name/CLionProjects/expression_system/expression_system/utility/string_utility.cpp -o CMakeFiles/expression_system.dir/expression_system/utility/string_utility.cpp.s

CMakeFiles/expression_system.dir/expression_system/parser/token.cpp.o: CMakeFiles/expression_system.dir/flags.make
CMakeFiles/expression_system.dir/expression_system/parser/token.cpp.o: ../expression_system/parser/token.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Name/CLionProjects/expression_system/emcc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/expression_system.dir/expression_system/parser/token.cpp.o"
	/mnt/c/Users/Name/emcc/emsdk/upstream/emscripten/em++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/expression_system.dir/expression_system/parser/token.cpp.o -c /mnt/c/Users/Name/CLionProjects/expression_system/expression_system/parser/token.cpp

CMakeFiles/expression_system.dir/expression_system/parser/token.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/expression_system.dir/expression_system/parser/token.cpp.i"
	/mnt/c/Users/Name/emcc/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Name/CLionProjects/expression_system/expression_system/parser/token.cpp > CMakeFiles/expression_system.dir/expression_system/parser/token.cpp.i

CMakeFiles/expression_system.dir/expression_system/parser/token.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/expression_system.dir/expression_system/parser/token.cpp.s"
	/mnt/c/Users/Name/emcc/emsdk/upstream/emscripten/em++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Name/CLionProjects/expression_system/expression_system/parser/token.cpp -o CMakeFiles/expression_system.dir/expression_system/parser/token.cpp.s

# Object files for target expression_system
expression_system_OBJECTS = \
"CMakeFiles/expression_system.dir/main.cpp.o" \
"CMakeFiles/expression_system.dir/expression_system/utility/named.cpp.o" \
"CMakeFiles/expression_system.dir/expression_system/utility/slice_view.cpp.o" \
"CMakeFiles/expression_system.dir/expression_system/utility/string_utility.cpp.o" \
"CMakeFiles/expression_system.dir/expression_system/parser/token.cpp.o"

# External object files for target expression_system
expression_system_EXTERNAL_OBJECTS =

expression_system.html: CMakeFiles/expression_system.dir/main.cpp.o
expression_system.html: CMakeFiles/expression_system.dir/expression_system/utility/named.cpp.o
expression_system.html: CMakeFiles/expression_system.dir/expression_system/utility/slice_view.cpp.o
expression_system.html: CMakeFiles/expression_system.dir/expression_system/utility/string_utility.cpp.o
expression_system.html: CMakeFiles/expression_system.dir/expression_system/parser/token.cpp.o
expression_system.html: CMakeFiles/expression_system.dir/build.make
expression_system.html: CMakeFiles/expression_system.dir/objects1.rsp
expression_system.html: CMakeFiles/expression_system.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Name/CLionProjects/expression_system/emcc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable expression_system.html"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/expression_system.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/expression_system.dir/build: expression_system.html

.PHONY : CMakeFiles/expression_system.dir/build

CMakeFiles/expression_system.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/expression_system.dir/cmake_clean.cmake
.PHONY : CMakeFiles/expression_system.dir/clean

CMakeFiles/expression_system.dir/depend:
	cd /mnt/c/Users/Name/CLionProjects/expression_system/emcc && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Name/CLionProjects/expression_system /mnt/c/Users/Name/CLionProjects/expression_system /mnt/c/Users/Name/CLionProjects/expression_system/emcc /mnt/c/Users/Name/CLionProjects/expression_system/emcc /mnt/c/Users/Name/CLionProjects/expression_system/emcc/CMakeFiles/expression_system.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/expression_system.dir/depend


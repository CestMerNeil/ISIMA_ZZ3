# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/neil/Code/ZZ3/CPP/Pokemon

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/neil/Code/ZZ3/CPP/Pokemon/build

# Include any dependencies generated for this target.
include CMakeFiles/pokemon_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/pokemon_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/pokemon_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pokemon_lib.dir/flags.make

CMakeFiles/pokemon_lib.dir/src/Pokemon.cpp.o: CMakeFiles/pokemon_lib.dir/flags.make
CMakeFiles/pokemon_lib.dir/src/Pokemon.cpp.o: /Users/neil/Code/ZZ3/CPP/Pokemon/src/Pokemon.cpp
CMakeFiles/pokemon_lib.dir/src/Pokemon.cpp.o: CMakeFiles/pokemon_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/neil/Code/ZZ3/CPP/Pokemon/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pokemon_lib.dir/src/Pokemon.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pokemon_lib.dir/src/Pokemon.cpp.o -MF CMakeFiles/pokemon_lib.dir/src/Pokemon.cpp.o.d -o CMakeFiles/pokemon_lib.dir/src/Pokemon.cpp.o -c /Users/neil/Code/ZZ3/CPP/Pokemon/src/Pokemon.cpp

CMakeFiles/pokemon_lib.dir/src/Pokemon.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pokemon_lib.dir/src/Pokemon.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/neil/Code/ZZ3/CPP/Pokemon/src/Pokemon.cpp > CMakeFiles/pokemon_lib.dir/src/Pokemon.cpp.i

CMakeFiles/pokemon_lib.dir/src/Pokemon.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pokemon_lib.dir/src/Pokemon.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/neil/Code/ZZ3/CPP/Pokemon/src/Pokemon.cpp -o CMakeFiles/pokemon_lib.dir/src/Pokemon.cpp.s

CMakeFiles/pokemon_lib.dir/src/Pokedex.cpp.o: CMakeFiles/pokemon_lib.dir/flags.make
CMakeFiles/pokemon_lib.dir/src/Pokedex.cpp.o: /Users/neil/Code/ZZ3/CPP/Pokemon/src/Pokedex.cpp
CMakeFiles/pokemon_lib.dir/src/Pokedex.cpp.o: CMakeFiles/pokemon_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/neil/Code/ZZ3/CPP/Pokemon/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/pokemon_lib.dir/src/Pokedex.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pokemon_lib.dir/src/Pokedex.cpp.o -MF CMakeFiles/pokemon_lib.dir/src/Pokedex.cpp.o.d -o CMakeFiles/pokemon_lib.dir/src/Pokedex.cpp.o -c /Users/neil/Code/ZZ3/CPP/Pokemon/src/Pokedex.cpp

CMakeFiles/pokemon_lib.dir/src/Pokedex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pokemon_lib.dir/src/Pokedex.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/neil/Code/ZZ3/CPP/Pokemon/src/Pokedex.cpp > CMakeFiles/pokemon_lib.dir/src/Pokedex.cpp.i

CMakeFiles/pokemon_lib.dir/src/Pokedex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pokemon_lib.dir/src/Pokedex.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/neil/Code/ZZ3/CPP/Pokemon/src/Pokedex.cpp -o CMakeFiles/pokemon_lib.dir/src/Pokedex.cpp.s

CMakeFiles/pokemon_lib.dir/src/Battle.cpp.o: CMakeFiles/pokemon_lib.dir/flags.make
CMakeFiles/pokemon_lib.dir/src/Battle.cpp.o: /Users/neil/Code/ZZ3/CPP/Pokemon/src/Battle.cpp
CMakeFiles/pokemon_lib.dir/src/Battle.cpp.o: CMakeFiles/pokemon_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/neil/Code/ZZ3/CPP/Pokemon/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/pokemon_lib.dir/src/Battle.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pokemon_lib.dir/src/Battle.cpp.o -MF CMakeFiles/pokemon_lib.dir/src/Battle.cpp.o.d -o CMakeFiles/pokemon_lib.dir/src/Battle.cpp.o -c /Users/neil/Code/ZZ3/CPP/Pokemon/src/Battle.cpp

CMakeFiles/pokemon_lib.dir/src/Battle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pokemon_lib.dir/src/Battle.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/neil/Code/ZZ3/CPP/Pokemon/src/Battle.cpp > CMakeFiles/pokemon_lib.dir/src/Battle.cpp.i

CMakeFiles/pokemon_lib.dir/src/Battle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pokemon_lib.dir/src/Battle.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/neil/Code/ZZ3/CPP/Pokemon/src/Battle.cpp -o CMakeFiles/pokemon_lib.dir/src/Battle.cpp.s

CMakeFiles/pokemon_lib.dir/src/Singleton.cpp.o: CMakeFiles/pokemon_lib.dir/flags.make
CMakeFiles/pokemon_lib.dir/src/Singleton.cpp.o: /Users/neil/Code/ZZ3/CPP/Pokemon/src/Singleton.cpp
CMakeFiles/pokemon_lib.dir/src/Singleton.cpp.o: CMakeFiles/pokemon_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/neil/Code/ZZ3/CPP/Pokemon/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/pokemon_lib.dir/src/Singleton.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/pokemon_lib.dir/src/Singleton.cpp.o -MF CMakeFiles/pokemon_lib.dir/src/Singleton.cpp.o.d -o CMakeFiles/pokemon_lib.dir/src/Singleton.cpp.o -c /Users/neil/Code/ZZ3/CPP/Pokemon/src/Singleton.cpp

CMakeFiles/pokemon_lib.dir/src/Singleton.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pokemon_lib.dir/src/Singleton.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/neil/Code/ZZ3/CPP/Pokemon/src/Singleton.cpp > CMakeFiles/pokemon_lib.dir/src/Singleton.cpp.i

CMakeFiles/pokemon_lib.dir/src/Singleton.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pokemon_lib.dir/src/Singleton.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/neil/Code/ZZ3/CPP/Pokemon/src/Singleton.cpp -o CMakeFiles/pokemon_lib.dir/src/Singleton.cpp.s

# Object files for target pokemon_lib
pokemon_lib_OBJECTS = \
"CMakeFiles/pokemon_lib.dir/src/Pokemon.cpp.o" \
"CMakeFiles/pokemon_lib.dir/src/Pokedex.cpp.o" \
"CMakeFiles/pokemon_lib.dir/src/Battle.cpp.o" \
"CMakeFiles/pokemon_lib.dir/src/Singleton.cpp.o"

# External object files for target pokemon_lib
pokemon_lib_EXTERNAL_OBJECTS =

libpokemon_lib.a: CMakeFiles/pokemon_lib.dir/src/Pokemon.cpp.o
libpokemon_lib.a: CMakeFiles/pokemon_lib.dir/src/Pokedex.cpp.o
libpokemon_lib.a: CMakeFiles/pokemon_lib.dir/src/Battle.cpp.o
libpokemon_lib.a: CMakeFiles/pokemon_lib.dir/src/Singleton.cpp.o
libpokemon_lib.a: CMakeFiles/pokemon_lib.dir/build.make
libpokemon_lib.a: CMakeFiles/pokemon_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/neil/Code/ZZ3/CPP/Pokemon/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libpokemon_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/pokemon_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pokemon_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pokemon_lib.dir/build: libpokemon_lib.a
.PHONY : CMakeFiles/pokemon_lib.dir/build

CMakeFiles/pokemon_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pokemon_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pokemon_lib.dir/clean

CMakeFiles/pokemon_lib.dir/depend:
	cd /Users/neil/Code/ZZ3/CPP/Pokemon/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/neil/Code/ZZ3/CPP/Pokemon /Users/neil/Code/ZZ3/CPP/Pokemon /Users/neil/Code/ZZ3/CPP/Pokemon/build /Users/neil/Code/ZZ3/CPP/Pokemon/build /Users/neil/Code/ZZ3/CPP/Pokemon/build/CMakeFiles/pokemon_lib.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/pokemon_lib.dir/depend


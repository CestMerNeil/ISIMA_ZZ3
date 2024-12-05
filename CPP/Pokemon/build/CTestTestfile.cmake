# CMake generated Testfile for 
# Source directory: /Users/neil/Code/ZZ3/CPP/Pokemon
# Build directory: /Users/neil/Code/ZZ3/CPP/Pokemon/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(PokemonTests "/Users/neil/Code/ZZ3/CPP/Pokemon/build/pokemon_tests")
set_tests_properties(PokemonTests PROPERTIES  _BACKTRACE_TRIPLES "/Users/neil/Code/ZZ3/CPP/Pokemon/CMakeLists.txt;53;add_test;/Users/neil/Code/ZZ3/CPP/Pokemon/CMakeLists.txt;0;")
subdirs("_deps/catch2-build")

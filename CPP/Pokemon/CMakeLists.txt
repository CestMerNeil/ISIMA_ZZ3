# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(PokemonCPP LANGUAGES CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable testing
include(CTest)

# Define the source directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/tests)

# Add the source files
set(SOURCES
    ${SRC_DIR}/Pokemon.cpp
    ${SRC_DIR}/Pokedex.cpp
    ${SRC_DIR}/Battle.cpp
    ${SRC_DIR}/Singleton.cpp
)

# Include directories
include_directories(${SRC_DIR})

# Add the main library
add_library(pokemon_lib ${SOURCES})

# Add the test executable
add_executable(pokemon_tests
    ${TEST_DIR}/test_pokemon.cpp
)

# Link the test executable to the main library
target_link_libraries(pokemon_tests pokemon_lib)

# Add Catch2 for testing
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.13.10 # Stable Catch2 version
)
FetchContent_MakeAvailable(Catch2)

# Link Catch2 to the test executable
target_link_libraries(pokemon_tests Catch2::Catch2)

# Enable tests
add_test(NAME PokemonTests COMMAND pokemon_tests)
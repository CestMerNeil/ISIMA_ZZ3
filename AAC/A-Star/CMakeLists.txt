cmake_minimum_required(VERSION 3.15)

# Project configuration
project(AStar VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source and header files
set(SOURCES
    src/main.cpp
    src/A_Star.cpp
    src/Grid.cpp
)

set(HEADERS
    include/A_Star.hpp
    include/Grid.hpp
)

# Create the executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories for headers
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Compiler warnings and optimization options
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Wextra -Wpedantic
)

# Handle build types
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(${PROJECT_NAME} PRIVATE -O3)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -g -O0 -Werror)
endif()
cmake_minimum_required(VERSION 3.10)
project(KMP_Search)

set(CMAKE_CXX_STANDARD 17)

add_executable(KMP_Search
    src/main.cpp
    src/KMP.cpp
    src/utils.cpp
)

target_include_directories(KMP_Search PRIVATE include)

add_executable(KMP_Tests
    tests/test_kmp.cpp
    src/KMP.cpp
    src/utils.cpp
)

target_include_directories(KMP_Tests PRIVATE include)
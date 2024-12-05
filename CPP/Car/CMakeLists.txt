cmake_minimum_required(VERSION 3.10)
project(Car)

set(CMAKE_CXX_STANDARD 17)

# 包含 src 文件夹
include_directories(src)

# 添加源文件
set(SOURCES
    src/Car.cpp
    src/ElectricCar.cpp
    src/CarFactory.cpp
    src/Garage.cpp
)

# 添加目标库
add_library(car_lib ${SOURCES})

# 添加测试
enable_testing()
add_subdirectory(test)
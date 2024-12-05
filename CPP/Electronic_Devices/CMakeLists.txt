cmake_minimum_required(VERSION 3.10)
project(ElectronicDevices)

set(CMAKE_CXX_STANDARD 17)

# 添加源文件目录
include_directories(src)

# 定义源文件
set(SOURCES
    src/Device.cpp
    src/SmartDevice.cpp
    src/DeviceFactory.cpp
    src/DeviceManager.cpp
    src/ProxyDevice.cpp
    src/DeviceObserver.cpp
)

# 添加目标库
add_library(devices_lib ${SOURCES})

# 添加测试子目录
enable_testing()
add_subdirectory(test)

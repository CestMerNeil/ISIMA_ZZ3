#!/bin/bash

# 项目根目录
PROJECT_ROOT="Electronic_Devices"

# 创建项目目录结构
echo "Creating project structure..."
mkdir -p $PROJECT_ROOT/src
mkdir -p $PROJECT_ROOT/test

# 创建 CMakeLists.txt 文件
echo "Creating CMakeLists.txt..."
cat <<EOF > $PROJECT_ROOT/CMakeLists.txt
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
add_library(devices_lib \${SOURCES})

# 添加测试子目录
enable_testing()
add_subdirectory(test)
EOF

# 创建 src 文件夹中的头文件和实现文件
echo "Creating source files..."
for FILE in Device SmartDevice DeviceFactory DeviceManager ProxyDevice DeviceObserver; do
    echo "#pragma once" > $PROJECT_ROOT/src/${FILE}.hpp
    echo "#include \"${FILE}.hpp\"" > $PROJECT_ROOT/src/${FILE}.cpp
done

# 创建 test/CMakeLists.txt
echo "Creating test/CMakeLists.txt..."
cat <<EOF > $PROJECT_ROOT/test/CMakeLists.txt
# 定义测试目标
add_executable(test_devices test_devices.cpp)

# 链接目标库
target_link_libraries(test_devices devices_lib)

# 注册测试
add_test(NAME TestDevices COMMAND test_devices)
EOF

# 创建测试文件
echo "Creating test file..."
cat <<EOF > $PROJECT_ROOT/test/test_devices.cpp
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Device.hpp"
#include "SmartDevice.hpp"
#include "DeviceFactory.hpp"
#include "DeviceManager.hpp"
#include "ProxyDevice.hpp"
#include "DeviceObserver.hpp"

// 在这里添加测试代码
TEST_CASE("Example") {
    REQUIRE(1 + 1 == 2);
}
EOF

echo "Project structure created successfully!"
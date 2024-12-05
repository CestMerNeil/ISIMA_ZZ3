# 定义测试目标
add_executable(test_devices test_devices.cpp)

# 链接目标库
target_link_libraries(test_devices devices_lib)

# 注册测试
add_test(NAME TestDevices COMMAND test_devices)

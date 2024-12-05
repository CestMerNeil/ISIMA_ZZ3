#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Device.hpp"
#include "SmartDevice.hpp"
#include "DeviceFactory.hpp"
#include "DeviceManager.hpp"
#include "ProxyDevice.hpp"
#include "DeviceObserver.hpp"

// 在这里添加测试代码
TEST_CASE("Example")
{
    REQUIRE(1 + 1 == 2);
}

// 构造函数测试
TEST_CASE("Device:Constructor")
{
    Device device("Sony", "Model123", 50);
    REQUIRE(device.getBrand() == "Sony");
    REQUIRE(device.getModel() == "Model123");
    REQUIRE(device.getPower() == 50);
}

// 拷贝与移动语义
TEST_CASE("Device:CopyConstructor")
{
    Device device("Samsung", "Galaxy", 20);
    Device copiedDevice = device;
    REQUIRE(copiedDevice.getBrand() == device.getBrand());
    REQUIRE(copiedDevice.getModel() == device.getModel());
    REQUIRE(copiedDevice.getPower() == device.getPower());
}

TEST_CASE("Device:MoveConstructor")
{
    Device device("LG", "SmartModel", 30);
    Device movedDevice = std::move(device);
    REQUIRE(movedDevice.getBrand() == "LG");
    REQUIRE(movedDevice.getModel() == "SmartModel");
    REQUIRE(movedDevice.getPower() == 30);
}

// 多态行为
TEST_CASE("Device:Polymorphism")
{
    Device *device = new SmartDevice("Apple", "HomePod", 25, true);
    REQUIRE(device->getType() == "Smart Device");
    delete device;
}

// 异常处理
TEST_CASE("Device:PowerException")
{
    Device device("Sony", "BasicModel", 0);
    REQUIRE_THROWS_AS(device.turnOn(), std::runtime_error);
}

// 工厂模式
TEST_CASE("DeviceFactory:CreateDevices")
{
    auto device = DeviceFactory::createDevice("Generic", "Sony", "ModelA", 50);
    REQUIRE(device->getBrand() == "Sony");
    REQUIRE(device->getType() == "Generic Device");

    auto smartDevice = DeviceFactory::createDevice("Smart", "Google", "Nest", 20);
    REQUIRE(smartDevice->getBrand() == "Google");
    REQUIRE(smartDevice->getType() == "Smart Device");
}

// 容器与分类
TEST_CASE("DeviceManager:StoreDevices")
{
    DeviceManager manager;

    auto device = DeviceFactory::createDevice("Generic", "Panasonic", "ModelX", 100);
    auto smartDevice = DeviceFactory::createDevice("Smart", "Amazon", "Echo", 30);

    manager.addDevice(std::move(device));
    manager.addDevice(std::move(smartDevice));

    REQUIRE(manager.getDeviceCount() == 2);
    REQUIRE(manager.getDevicesByType("Smart Device").size() == 1);
    REQUIRE(manager.getDevicesByType("Generic Device").size() == 1);
}

// 智能指针测试
TEST_CASE("DeviceManager:SmartPointers")
{
    auto device = std::make_shared<Device>("Dell", "XPS", 65);
    auto smartDevice = std::make_shared<SmartDevice>("Microsoft", "Surface", 35, true);

    REQUIRE(device.use_count() == 1);
    REQUIRE(smartDevice.use_count() == 1);

    std::shared_ptr<Device> sharedDevice = device;
    REQUIRE(device.use_count() == 2);
}

// 运算符重载
TEST_CASE("Device:OperatorOverload")
{
    Device device1("BrandA", "Model1", 50);
    Device device2("BrandA", "Model2", 50);

    REQUIRE(device1 == device2);   // 比较品牌
    REQUIRE(!(device1 < device2)); // 比较型号字母顺序
}

// 静态成员
TEST_CASE("Device:StaticMembers")
{
    REQUIRE(Device::getTotalDevices() == 0);

    Device device1("BrandA", "Model1", 50);
    Device device2("BrandB", "Model2", 30);

    REQUIRE(Device::getTotalDevices() == 2);
}

/*
// 模板与泛型编程
TEST_CASE("DeviceManager:TemplateFunctionality")
{
    DeviceManager<SmartDevice> smartDeviceManager;
    smartDeviceManager.addDevice(SmartDevice("Apple", "iPhone", 15, true));
    REQUIRE(smartDeviceManager.getDeviceCount() == 1);
}
*/

// 观察者模式
TEST_CASE("DeviceObserver:Notification")
{
    DeviceObserver observer;
    SmartDevice device("Google", "Nest", 10, true);

    device.addObserver(&observer);
    device.setPower(0); // 触发低电量通知

    REQUIRE(observer.getNotificationCount() == 1);
}
/*
// 责任链模式
TEST_CASE("DeviceManager:ResponsibilityChain")
{
    DeviceManager manager;

    auto device1 = DeviceFactory::createDevice("Generic", "Sony", "ModelA", 50);
    auto device2 = DeviceFactory::createDevice("Smart", "Google", "Nest", 20);

    manager.addDevice(std::move(device1));
    manager.addDevice(std::move(device2));

    REQUIRE(manager.processDevices("TurnOn") == 2); // 所有设备都被处理
}

// 状态模式
TEST_CASE("SmartDevice:StateManagement")
{
    SmartDevice device("Amazon", "Echo", 20, true);
    REQUIRE(device.getState() == "Off");

    device.turnOn();
    REQUIRE(device.getState() == "On");

    device.turnOff();
    REQUIRE(device.getState() == "Off");
}
*/
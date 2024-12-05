#pragma once

#include <vector>
#include "Device.hpp"
#include "SmartDevice.hpp"

class DeviceManager
{
private:
    std::vector<std::unique_ptr<Device>> lists;
    int counter;

public:
    DeviceManager() : counter(0) {}
    void addDevice(std::unique_ptr<Device> device)
    {
        lists.push_back(std::move(device));
        ++counter;
    }

    inline int getDeviceCount() { return counter; }
    std::vector<Device *> getDevicesByType(std::string type)
    {
        std::vector<Device *> devices;
        for (const auto &list : lists)
        {
            if (list->getType() == type)
            {
                devices.push_back(list.get());
            }
        }
        return devices;
    }
};

/*
template <typename T>
class DeviceManager
{
private:
    std::vector<T> lists;

public:
};
*/
#pragma once

#include "Device.hpp"
#include "SmartDevice.hpp"

#include <memory>
#include <stdexcept>

class DeviceFactory
{

public:
    static std::unique_ptr<Device> createDevice(const std::string &type, const std::string &brand, const std::string &model, const int &power)
    {
        if (type == "Generic")
        {
            return std::make_unique<Device>(brand, model, power);
        }
        else if (type == "Smart")
        {
            return std::make_unique<SmartDevice>(brand, model, power);
        }
        else
        {
            throw std::runtime_error("");
        }
    }
};
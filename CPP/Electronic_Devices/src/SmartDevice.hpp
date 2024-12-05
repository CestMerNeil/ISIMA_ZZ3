#pragma once

#include "Device.hpp"

class SmartDevice : public Device
{
public:
    SmartDevice(std::string brand, std::string model, int power, bool on) : Device(brand, model, power, on) {}
    SmartDevice(std::string brand, std::string model, int power) : Device(brand, model, power, false) {}
    inline std::string getType() const override { return "Smart Device"; }
};

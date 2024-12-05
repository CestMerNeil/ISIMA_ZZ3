#pragma once

#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "DeviceObserver.hpp"

class Device
{
private:
    std::string brand;
    std::string model;
    int power;
    bool on;
    static int No;
    std::vector<DeviceObserver *> observers;

public:
    Device(std::string brand, std::string model, int power) : brand(brand), model(model), power(power), on(false)
    {
        No++;
    }
    Device(std::string brand, std::string model, int power, bool on) : brand(brand), model(model), power(power), on(on) { No++; }
    Device(const Device &c) : brand(c.brand), model(c.model), power(c.power), on(c.on) { No++; }
    Device(Device &&c) noexcept : brand(std::move(c.brand)), model(std::move(c.model)), power(c.power), on(c.on)
    {
        c.power = 0;
        No++;
    }
    ~Device() { No--; }
    inline std::string getBrand() const { return brand; }
    inline std::string getModel() const { return model; }
    inline void setPower(int p)
    {
        if (p == 0)
        {
            notifyObservers("");
        }
        power = p;
    }
    inline int getPower() const { return power; }
    inline virtual std::string getType() const { return "Generic Device"; }
    void turnOn()
    {
        if (power == 0)
        {
            throw std::runtime_error("");
        }
        else
        {
            on = true;
        }
    }
    friend bool operator==(const Device &lhs, const Device &rhs)
    {
        return lhs.brand == rhs.brand;
    }
    friend bool operator<(const Device &lhs, const Device &rhs)
    {
        return lhs.model > rhs.model;
    }
    inline static int getTotalDevices() { return No; }

    inline void addObserver(DeviceObserver *observer) { observers.push_back(observer); }
    inline void removeObserver(DeviceObserver *observer) { observers.erase(std::remove(observers.begin(), observers.end(), observer)); }
    inline void notifyObservers(const std::string &msg)
    {
        for (auto observer : observers)
        {
            observer->update(msg);
        }
    }
};

#pragma once

#include "Car.hpp"

class ElectricCar : public Car
{
private:
    int batteryLevel;

public:
    ElectricCar(std::string brand, int speed, int batteryLevel) : Car(brand, speed), batteryLevel(batteryLevel) {}
    inline int getBatteryLevel() const { return batteryLevel; }
    inline std::string getCarType() override { return "Electric Car"; }
    void drive(int distance) override
    {
        if (distance > batteryLevel)
        {
            throw std::runtime_error("No Enough BATTERY!");
        }
        else
        {
            batteryLevel -= distance;
        }
    }
};
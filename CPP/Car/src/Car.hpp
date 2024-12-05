#pragma once

#include <iostream>
#include <string>
#include <exception>

class Car
{
private:
    std::string brand;
    int speed;
    int fuel;

public:
    Car(std::string brand, int speed, int fuel) : brand(brand), speed(speed), fuel(fuel) {}
    Car(std::string brand, int speed) : brand(brand), speed(speed), fuel(0) {}
    Car(const Car &c) : brand(c.brand), speed(c.speed), fuel(c.fuel) {}
    Car(Car &&c) noexcept : brand(std::move(c.brand)), speed(c.speed), fuel(c.fuel)
    {
        c.speed = 0;
        c.fuel = 0;
    }
    inline std::string getBrand() const { return brand; }
    inline int getSpeed() const { return speed; }
    inline int getFuel() const { return fuel; }
    virtual std::string getCarType() { return "Generic Car"; }
    virtual void drive(int distance)
    {
        if (distance > fuel)
        {
            throw std::runtime_error("No Enough FUEL!");
        }
        else
        {
            fuel -= distance;
        }
    }
};

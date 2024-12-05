#pragma once

#include "Car.hpp"
#include "ElectricCar.hpp"
#include <memory>
#include <stdexcept>

// 工厂模式
class CarFactory
{
public:
    static std::unique_ptr<Car> createCar(const std::string &type, const std::string &brand, int speed);
};
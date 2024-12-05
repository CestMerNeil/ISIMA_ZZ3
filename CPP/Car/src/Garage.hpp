#pragma once

#include "Car.hpp"
#include "ElectricCar.hpp"

#include <vector>

class Garage
{
private:
    std::vector<std::unique_ptr<Car>> cars;
    int counter;

public:
    Garage() : counter(0) {}
    void addCar(std::unique_ptr<Car> c)
    {
        cars.push_back(std::move(c));
        ++counter;
    }
    inline int getCarCount() const { return counter; }
    std::vector<Car *> getCarByType(const std::string &type) const
    {
        std::vector<Car *> fCars;
        for (const auto &car : cars)
        {
            if (car->getCarType() == type)
            {
                fCars.push_back(car.get());
            }
        }
        return fCars;
    }
};
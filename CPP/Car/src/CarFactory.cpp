#include "CarFactory.hpp"

std::unique_ptr<Car> CarFactory::createCar(const std::string &type, const std::string &brand, int speed)
{
    if (type == "Generic")
    {
        return std::make_unique<Car>(brand, speed, 50);
    }
    else if (type == "Electric")
    {
        return std::make_unique<ElectricCar>(brand, speed, 100);
    }
    else
    {
        throw std::invalid_argument("Unknown car type: " + type);
    }
}
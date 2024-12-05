#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Car.hpp"
#include "ElectricCar.hpp"
#include "CarFactory.hpp"
#include "Garage.hpp"

TEST_CASE("Car:Constructor")
{
    Car car("Toyota", 120, 50);
    REQUIRE(car.getBrand() == "Toyota");
    REQUIRE(car.getSpeed() == 120);
    REQUIRE(car.getFuel() == 50);

    ElectricCar tesla("Tesla", 150, 100);
    REQUIRE(tesla.getBrand() == "Tesla");
    REQUIRE(tesla.getSpeed() == 150);
    REQUIRE(tesla.getBatteryLevel() == 100);
}

TEST_CASE("Car:CopyConstructor")
{
    Car car("Honda", 100, 40);
    Car copyCar = car;
    REQUIRE(copyCar.getBrand() == car.getBrand());
    REQUIRE(copyCar.getSpeed() == car.getSpeed());
    REQUIRE(copyCar.getFuel() == car.getFuel());
}

TEST_CASE("Car:MoveConstructor")
{
    Car car("BMW", 130, 60);
    Car movedCar = std::move(car);
    REQUIRE(movedCar.getBrand() == "BMW");
    REQUIRE(movedCar.getFuel() == 60);
}

TEST_CASE("Car:Polymorphism")
{
    Car *car = new ElectricCar("Nissan Leaf", 90, 80);
    REQUIRE(car->getCarType() == "Electric Car");
    delete car;
}

TEST_CASE("Car:OutOfFuelException")
{
    Car car("Toyota", 120, 10);
    REQUIRE_THROWS_AS(car.drive(200), std::runtime_error);
}

TEST_CASE("ElectricCar:BatteryDepletedException")
{
    ElectricCar tesla("Tesla", 150, 5);
    REQUIRE_THROWS_AS(tesla.drive(30), std::runtime_error);
}

TEST_CASE("CarFactory:CreateCars")
{
    auto car = CarFactory::createCar("Generic", "Ford", 100);
    REQUIRE(car->getBrand() == "Ford");
    REQUIRE(car->getCarType() == "Generic Car");

    auto electricCar = CarFactory::createCar("Electric", "Tesla", 150);
    REQUIRE(electricCar->getBrand() == "Tesla");
    REQUIRE(electricCar->getCarType() == "Electric Car");
}

TEST_CASE("Garage:StoreCars")
{
    Garage garage;

    auto car = CarFactory::createCar("Generic", "Ford", 100);
    auto electricCar = CarFactory::createCar("Electric", "Nissan Leaf", 90);

    garage.addCar(std::move(car));
    garage.addCar(std::move(electricCar));

    REQUIRE(garage.getCarCount() == 2);
    REQUIRE(garage.getCarByType("Electric Car").size() == 1);
    REQUIRE(garage.getCarByType("Generic Car").size() == 1);
}

TEST_CASE("Garage:SmartPointers")
{
    auto car = std::make_shared<Car>("Honda", 110, 30);
    auto electricCar = std::make_shared<ElectricCar>("Tesla", 150, 80);

    REQUIRE(car.use_count() == 1);
    REQUIRE(electricCar.use_count() == 1);

    std::shared_ptr<Car> sharedCar = car;
    REQUIRE(car.use_count() == 2);
}

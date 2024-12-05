#ifndef CARTEISIEN_HPP
#define CARTEISIEN_HPP

#include <iostream>

class Cartesien
{
private:
    double x;
    double y;

public:
    Cartesien() : x(0), y(0) {};
    Cartesien(double x_val, double y_val) : x(x_val), y(y_val) {};

    double getX() const { return x; };
    double getY() const { return y; };
    void setX(double x_val) { this->x = x_val; };
    void setY(double y_val) { this->y = y_val; };
};

#endif
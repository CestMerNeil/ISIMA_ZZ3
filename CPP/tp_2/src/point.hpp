// tp_2/src/point.hpp

#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

class Point
{
public:
    Point() : x(0), y(0) {};
    Point(double x_val, double y_val) : x(x_val), y(y_val) {};

    void setX(double x_val) { this->x = x_val; };
    void setY(double y_val) { this->y = y_val; };

private:
    double x;
    double y;
};

#endif
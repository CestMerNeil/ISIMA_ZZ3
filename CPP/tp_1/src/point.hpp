// tp_1/src/point.hpp

#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

class Cartesien;
class Polaire;

class Point
{
private:
    double x;
    double y;

public:
    Point();
    Point(double x, double y);
    virtual void afficher(std::ostream &flux) const = 0;
    friend std::ostream &operator<<(std::ostream &flux, const Point &p);
    void setX(double x);
    void setY(double y);

    virtual void convertir(Cartesien &c) const = 0;
    virtual void convertir(Polaire &p) const = 0;
};

#endif
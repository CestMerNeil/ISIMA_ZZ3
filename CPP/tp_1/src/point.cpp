#include "point.hpp"

Point::Point(const double x, const double y) : x(x), y(y) {}
Point::Point() : x(0.0), y(0.0) {}

void Point::afficher(std::ostream &flux) const {
    flux << "(x=" << x << ";y=" << y << ")";
}

std::ostream &operator<<(std::ostream &flux, const Point &p) {
    p.afficher(flux);
    return flux;
}

void Point::setX(const double x) {
    this->x = x;
}

void Point::setY(const double y) {
    this->y = y;
}
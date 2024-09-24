#include "cartesien.hpp"

Cartesien::Cartesien(const double x, const double y) : x(x), y(y) {}
Cartesien::Cartesien() : x(0.0), y(0.0) {}
Cartesien::Cartesien(const Polaire& p) {
    p.convertir(*this);
}

double Cartesien::getX() const {
    return x;
}

double Cartesien::getY() const {
    return y;
}

void Cartesien::setX(const double x) {
    this->x = x;
}

void Cartesien::setY(const double y) {
    this->y = y;
}

void Cartesien::afficher(std::ostream &flux) const {
    flux << "(x=" << x << ";y=" << y << ")";
}

void Cartesien::convertir(Polaire& p) const {
    double distance = sqrt(x * x + y * y);
    double angle = atan2(y, x) * 180.0 / M_PI;
    p.setDistance(distance);
    p.setAngle(angle);
}

void Cartesien::convertir(Cartesien& c) const {
    c.setX(x);
    c.setY(y);
}
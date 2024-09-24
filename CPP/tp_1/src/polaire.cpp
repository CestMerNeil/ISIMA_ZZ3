#include "polaire.hpp"

Polaire::Polaire(const double a, const double d) : angle(a), distance(d) {}
Polaire::Polaire() : angle(0.0), distance(0.0) {}
Polaire::Polaire(const Cartesien& c) {
    c.convertir(*this);
}

double Polaire::getAngle() const {
    return angle;
}

double Polaire::getDistance() const {
    return distance;
}

void Polaire::setAngle(const double a) {
    angle = a;
}

void Polaire::setDistance(const double d) {
    distance = d;
}

void Polaire::afficher(std::ostream &flux) const {
    flux << "(a=" << angle << ";d=" << distance << ")";
}


void Polaire::convertir(Cartesien& c) const {
    double angleRadians = angle * M_PI / 180.0;
    double x = distance * cos(angleRadians);
    double y = distance * sin(angleRadians);
    c.setX(x);
    c.setY(y);
}

void Polaire::convertir(Polaire& p) const {
    p.setAngle(angle);
    p.setDistance(distance);
}
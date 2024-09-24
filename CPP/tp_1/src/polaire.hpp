#ifndef POLAIRE_HPP
#define POLAIRE_HPP

#include "point.hpp"
#include "cartesien.hpp"
#include <cmath>

class Polaire : public Point {
    private:
    double angle;
    double distance;
    public:
    Polaire();
    Polaire(double angle, double distance);
    Polaire(const Cartesien& c);
    double getAngle() const;
    double getDistance() const;
    void setAngle(double angle);
    void setDistance(double distance);
    void afficher(std::ostream& flux) const override;
    void convertir(Cartesien& c) const override;
    void convertir(Polaire& p) const override;
};

#endif
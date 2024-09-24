#ifndef CARTESIEN_HPP
#define CARTESIEN_HPP

#include "point.hpp"
#include "polaire.hpp"
#include <cmath>

class Cartesien : public Point {
    private:
    double x;
    double y;

    public:
    Cartesien();
    Cartesien(double x, double y);
    Cartesien(const Polaire& p);
    double getX() const;
    double getY() const;
    void setX(double x);
    void setY(double y);
    void afficher(std::ostream &flux) const override;
    void convertir(Polaire& p) const override;
    void convertir(Cartesien& c) const override;
};

#endif
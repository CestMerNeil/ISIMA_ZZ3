// barycentre.hpp
#ifndef BARYCENTRE_HPP
#define BARYCENTRE_HPP

#include "nuage.hpp"
#include "cartesien.hpp"

Cartesien barycentre_v1(const Nuage<Cartesien> nuage)
{
    if (nuage.size() == 0)
    {
        return Cartesien(0.0, 0.0);
    }

    double sumX = 0.0;
    double sumY = 0.0;
    for (const auto &p : nuage)
    {
        sumX += p.getX();
        sumY += p.getY();
    }

    return Cartesien(sumX / nuage.size(), sumY / nuage.size());
}

#endif // BARYCENTRE_HPP
#include "nuage.hpp"

Nuage::Nuage() {}

size_t Nuage::size() const
{
    return points.size();
}

void Nuage::ajouter(Cartesien &c)
{
    points.push_back(new Cartesien(c));
}

void Nuage::ajouter(Polaire &p)
{
    points.push_back(new Polaire(p));
}

void Nuage::ajouter(Point *p)
{
    points.push_back(p);
}

Nuage::const_iterator Nuage::begin() const
{
    return points.begin();
}

Nuage::const_iterator Nuage::end() const
{
    return points.end();
}

Nuage::~Nuage()
{
    for (auto point : points)
    {
        delete point;
    }
}

Cartesien barycentre(const Nuage &n)
{
    double sumX = 0.0;
    double sumY = 0.0;
    size_t size = n.size();

    for (const Point *p : n)
    {
        Cartesien c;
        p->convertir(c);
        sumX += c.getX();
        sumY += c.getY();
    }

    return Cartesien(sumX / size, sumY / size);
}
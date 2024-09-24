#ifndef NUAGE_HPP
#define NUAGE_HPP

#include <vector>
#include "cartesien.hpp"
#include "polaire.hpp"
#include "point.hpp"



class Nuage {
    private:
    std::vector<Point*> points;
    public:
    Nuage();
    size_t size() const;
    void ajouter(Cartesien& c);
    void ajouter(Polaire& p);

    using const_iterator = std::vector<Point*>::const_iterator;
    const_iterator begin() const;
    const_iterator end() const;
    ~Nuage();
};

Cartesien barycentre(const Nuage& n);

class BarycentreCartesien {
    public:
    Cartesien operator()(const Nuage& n) const {
        return barycentre(n);
    }
};

class BarycentrePolaire {
    public:
    Polaire operator()(const Nuage& n) const {
        Cartesien c = barycentre(n);
        return Polaire(c);
    }
};

#endif
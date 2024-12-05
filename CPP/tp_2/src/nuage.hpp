// tp_2/src/nuage.hpp

#ifndef NUAGE_HPP
#define NUAGE_HPP

#include <vector>
#include "point.hpp"
#include "cartesien.hpp"
#include "polaire.hpp"
#include "barycentre.hpp"

template <typename T>
class Nuage
{
private:
    std::vector<T> points;

public:
    Nuage() : points() {};
    void ajouter(const T &p) { points.push_back(p); };
    size_t size() const { return points.size(); };

    using const_iterator = typename std::vector<T>::const_iterator;
    const_iterator begin() const { return points.begin(); };
    const_iterator end() const { return points.end(); };
};

#endif
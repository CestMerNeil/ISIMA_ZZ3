#ifndef ECHANTILLON_HPP
#define ECHANTILLON_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "valeur.hpp"

class Echantillon
{
private:
    std::vector<Valeur> valeurs;

public:
    Echantillon() {}
    int getTaille() { return valeurs.size(); }
    void ajouter(const double n) { valeurs.push_back(Valeur(n)); }
    Valeur getMinimum()
    {
        if (valeurs.size() == 0)
        {
            throw std::domain_error("erreur");
        }
        std::sort(valeurs.begin(), valeurs.end());
        return valeurs[0];
    }
    Valeur getMaximum()
    {
        if (valeurs.size() == 0)
        {
            throw std::domain_error("erreur");
        }
        std::sort(valeurs.begin(), valeurs.end());
        return valeurs[valeurs.size() - 1];
    }
    Valeur getValeur(const unsigned i)
    {
        if (i >= valeurs.size())
        {
            throw std::out_of_range("erreur");
        }
        return valeurs[i];
    }
};

#endif // ECHANTILLON_HPP
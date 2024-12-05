#ifndef CLASSE_HPP
#define CLASSE_HPP

#include <iostream>
#include <vector>
#include "echantillon.hpp"
#include "valeur.hpp"

class Classe
{
private:
    double borneInf;
    double borneSup;
    unsigned quantite;

public:
    Classe(double inf, double sup) : borneInf(inf), borneSup(sup), quantite(0u) {}
    Classe(const Classe &c) { *this = c; }
    Classe(Classe &&c) { *this = std::move(c); }
    double getBorneInf() const { return borneInf; }
    double getBorneSup() const { return borneSup; }
    double getQuantite() const { return quantite; }
    void setBorneInf(double inf) { borneInf = inf; }
    void setBorneSup(double sup) { borneSup = sup; }
    void setQuantite(unsigned q) { quantite = q; }
    void ajouter() { quantite++; }
    Classe &operator=(const Classe &c)
    {
        borneInf = c.borneInf;
        borneSup = c.borneSup;
        quantite = c.quantite;
        return *this;
    }
    bool operator<(const Classe &c) const { return borneInf < c.borneInf; }
    bool operator>(const Classe &c) const { return borneInf > c.borneInf; }
};

#endif // CLASSE_HPP

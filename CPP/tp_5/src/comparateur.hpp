#ifndef COMPARATEUR_HPP
#define COMPARATEUR_HPP

#include "classe.hpp"
#include <vector>
#include <functional>

class ComparateurQuantite
{
public:
    ComparateurQuantite() {}
    ComparateurQuantite(double inf, double sup, unsigned q) : borneInf(inf), borneSup(sup), quantite(q) {}
    double getBorneInf() const { return borneInf; }
    double getBorneSup() const { return borneSup; }
    unsigned getQuantite() const { return quantite; }
    void setBorneInf(double inf) { borneInf = inf; }
    void setBorneSup(double sup) { borneSup = sup; }
    void setQuantite(unsigned q) { quantite = q; }
    void ajouter() { quantite++; }
    inline bool operator()(const Classe &a, const Classe &b) { return a.getQuantite() < b.getQuantite(); }

private:
    double borneInf;
    double borneSup;
    unsigned quantite;
};

#endif // COMPARATEUR_HPP
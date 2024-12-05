#ifndef HISTOGRAMME_HPP
#define HISTOGRAMME_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include "valeur.hpp"
#include "echantillon.hpp"
#include "classe.hpp"
#include "comparateur.hpp"

template <typename Compare = std::less<Classe>>
class Histogramme
{
private:
    std::vector<Classe> classes;
    std::vector<std::pair<Classe, Valeur>> valeurs;
    Compare comparer;

public:
    Histogramme(double bornesInf, double bornesSup, int nbClasse, Compare comp = Compare()) : comparer(comp)
    {
        double class_size = (bornesSup - bornesInf) / nbClasse;
        for (int i = 0; i < nbClasse; ++i)
        {
            double inf = bornesInf + (i * class_size);
            double sup = bornesInf + ((i + 1) * class_size);
            Classe c(inf, sup);
            classes.push_back(c);
            valeurs.emplace_back(c, Valeur());
        }
        std::sort(classes.begin(), classes.end(), comparer);
    }
    const std::vector<Classe> &getClasses() { return classes; }
    void ajouter(Echantillon &e)
    {
        for (int i = 0; i < e.getTaille(); ++i)
        {
            Valeur v = e.getValeur(i);
            for (int j = 0; j < classes.size(); ++j)
            {
                if (v.getNombre() >= classes[j].getBorneInf() && v.getNombre() < classes[j].getBorneSup())
                {
                    classes[j].ajouter();
                    break;
                }
            }
        }
    }
    void ajouter(const double &v)
    {
        for (int j = 0; j < classes.size(); ++j)
        {
            if (v >= classes[j].getBorneInf() && v < classes[j].getBorneSup())
            {
                classes[j].ajouter();
                break;
            }
        }
    }
    inline const std::vector<std::pair<Classe, Valeur>> &getValeurs() { return valeurs; }
};

#endif // HISTOGRAMME_HPP
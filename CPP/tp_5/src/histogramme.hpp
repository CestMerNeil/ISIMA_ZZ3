#ifndef HISTOGRAMME_HPP
#define HISTOGRAMME_HPP

#include <iostream>
#include "valeur.hpp"
#include "echantillon.hpp"
#include "classe.hpp"

class Histogramme
{
private:
    std::vector<Classe> classes;

public:
    Histogramme(double bornesInf, double bornesSup, int nbClasse)
    {
        double class_size = (bornesSup - bornesInf) / nbClasse;
        for (int i = 0; i < nbClasse; ++i)
        {
            double inf = bornesInf + (i * class_size);
            double sup = bornesInf + ((i + 1) * class_size);
            classes.push_back(Classe(inf, sup));
        }
    }
    std::vector<Classe> getClasses() const { return classes; }
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
};

#endif // HISTOGRAMME_HPP
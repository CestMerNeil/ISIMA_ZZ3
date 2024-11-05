#ifndef VALEUR_HPP
#define VALEUR_HPP

#include <iostream>

class Valeur
{
private:
    double nombre;
    std::string nom;

public:
    Valeur(const double n) : nombre(n) {}
    Valeur(const double n, const std::string &s) : nombre(n), nom(s) {}
    Valeur() : nombre(0.0), nom("inconnu") {}
    double getNombre() const { return nombre; }
    double getNote() const { return nombre; }
    std::string getEtudiant() const { return nom; }
    void setNombre(const double n) { nombre = n; }
    void setNote(const double n) { nombre = n; }
    void setEtudiant(const std::string &s) { nom = s; }
    friend bool operator>(const Valeur &v1, const Valeur &v2) { return v1.nombre > v2.nombre; }
    friend bool operator<(const Valeur &v1, const Valeur &v2) { return v1.nombre < v2.nombre; }
};

#endif
#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <iostream>

class Item
{
private:
    std::string nom;
    bool vendable;
    double prix;

public:
    Item(std::string nom) : nom(nom), vendable(false), prix(.0) {}
    Item(std::string nom, int prix) : nom(nom), vendable(false), prix(double(prix)) {}
    Item(std::string nom, bool vendable, double prix) : nom(nom), vendable(vendable), prix(prix) {}
    Item(Item &i) : nom(i.getNom()), vendable(i.getVendable()), prix(i.getPrix()) {}
    inline std::string getNom() { return nom; }
    inline bool getVendable() { return vendable; }
    inline int getPrix() { return (int)prix; }
};

#endif
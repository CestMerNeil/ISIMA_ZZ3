#pragma once

#include <string>
#include <iostream>
#include <vector>

class Item
{
private:
    std::string nom;
    bool vendable;
    int prix;

public:
    Item(std::string nom) : nom(nom), vendable(false), prix(0)
    {
    }
    Item(std::string nom, int prix) : nom(nom), prix(prix)
    {
        if (prix == 0)
        {
            vendable = false;
        }
        else
        {
            vendable = true;
        }
    }
    Item(const Item &i) : nom(i.nom), vendable(i.vendable), prix(i.prix) {}
    inline std::string getNom() const { return nom; }
    inline bool estVendable() const { return vendable; }
    inline int getPrix() const { return prix; }
    virtual ~Item() = default;
    virtual std::string getType() const { return "Item"; }
    bool operator<(const Item &i) const
    {
        return nom < i.nom;
    }
    // inline Fabricant *getFabricant() const { return fabricant; }
};
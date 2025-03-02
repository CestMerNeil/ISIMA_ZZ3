#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "item.hpp"

class Fabricant
{
private:
    std::string nom;
    bool hasItems;
    std::vector<std::unique_ptr<Item>> list;

public:
    Fabricant(std::string nom) : nom(nom), hasItems(false) {}
    inline std::string getNom() const { return nom; }
    inline bool hasItemsEnProduction() const { return hasItems; }
    inline void ajouterProduction(std::string name)
    {
        list.push_back(std::make_unique<Item>("[" + nom + "] " + name));
        hasItems = true;
    }

    Item *produire(std::string nom) const
    {
        for (auto &it : list)
        {
            if (it->getNom().find(nom) != std::string::npos)
            {
                return it.get();
            }
        }
        return nullptr;
    }
};
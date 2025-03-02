#pragma once

#include "item.hpp"
#include <vector>
#include <map>
#include <algorithm>

class Inventaire
{
private:
    std::vector<Item *> lists;
    int num;

public:
    enum class Categorie : char
    {
        RARE = 'R',
        CONSOMMABLE = 'C',
        ARME = 'A',
        NORMAL = 'N'
    };
    using list_t = std::vector<Item *>;
    std::map<Categorie, list_t> maps;

    Inventaire() : num(0)
    {
        maps[Categorie::RARE] = list_t();
        maps[Categorie::CONSOMMABLE] = list_t();
        maps[Categorie::ARME] = list_t();
        maps[Categorie::NORMAL] = list_t();
    }
    inline int getTaille() const { return num; }
    inline void ajouter(Item *i, Categorie categorie = Categorie::NORMAL)
    {
        if (i->getType() == "Arme")
        {
            categorie = Categorie::ARME;
        }
        maps[categorie].push_back(i);
        ++num;
        std::sort(maps[categorie].begin(), maps[categorie].end(), [](Item *a, Item *b)
                  { return a->getNom() < b->getNom(); });
        std::cout << "Added item: " << i->getNom() << " to category: " << static_cast<char>(categorie) << std::endl;
    }
    const list_t &getItemsParCategorie(Categorie categorie) const
    {
        static const list_t emptyList;
        auto it = maps.find(categorie);
        return it != maps.end() ? it->second : emptyList;
    }
};
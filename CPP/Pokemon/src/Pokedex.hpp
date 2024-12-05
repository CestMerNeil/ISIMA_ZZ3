#ifndef POKEDEX_HPP
#define POKEDEX_HPP

#include <vector>
#include "Pokemon.hpp"

class Pokedex
{
private:
    std::vector<std::unique_ptr<Pokemon>> list;

public:
    Pokedex() {}
    void addPokemon(std::unique_ptr<Pokemon> pokemon) { list.push_back(std::move(pokemon)); }
    bool contains(const std::string &name) const
    {
        for (const auto &pokemon : list)
        {
            if (pokemon->getName() == name)
            {
                return true;
            }
        }
        return false;
    }
};

#endif
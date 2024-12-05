#pragma once

#include "Pokemon.hpp"
#include <memory>
#include <stdexcept>
#include <string>

class PokemonFactory
{
public:
    static std::unique_ptr<Pokemon> createCharmander(int level)
    {
        int hp = 50 + level * 5;
        int attack = 10 + level * 2;
        return std::make_unique<Pokemon>("Charmander", level, hp, attack);
    }

    static std::unique_ptr<Pokemon> createBulbasaur(int level)
    {
        int hp = 60 + level * 5;
        int attack = 8 + level * 2;
        return std::make_unique<Pokemon>("Bulbasaur", level, hp, attack);
    }

    static std::unique_ptr<Pokemon> createPokemon(const std::string &type, int level = 1)
    {
        if (type == "Charmander")
        {
            return createCharmander(level);
        }
        else if (type == "Bulbasaur")
        {
            return createBulbasaur(level);
        }
        else
        {
            throw std::invalid_argument("Unknown Pokemon type");
        }
    }
};

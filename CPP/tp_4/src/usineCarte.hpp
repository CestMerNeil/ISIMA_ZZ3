#ifndef USINECARTE
#define USINECARTE

#include "carte.hpp"
#include <memory>
#include <vector>

class UsineCarte
{
public:
    UsineCarte()
    {
        for (int i = 0; i < 52; ++i)
        {
            carte.push_back(std::make_unique<Carte>(i));
        }
    };

    UsineCarte(const UsineCarte &) = delete;

    std::unique_ptr<Carte> getCarte()
    {
        if (carte.size() > 0)
        {
            auto firstCarte = std::move(carte.front());
            carte.erase(carte.begin());
            return firstCarte;
        }
        else
        {
            return nullptr;
        }
    };

private:
    int num = 0;
    std::vector<std::unique_ptr<Carte>> carte;
};

#endif
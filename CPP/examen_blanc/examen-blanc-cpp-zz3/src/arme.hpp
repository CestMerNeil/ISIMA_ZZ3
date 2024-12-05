#ifndef ARME_HPP
#define ARME_HPP

#include <item.hpp>

class Arme : public Item
{
private:
public:
    Arme(std::string nom, int vendable, int prix) : Item(nom + "[" + std::to_string(prix) + "]", static_cast<bool>(vendable), (double)prix) {}
};

#endif
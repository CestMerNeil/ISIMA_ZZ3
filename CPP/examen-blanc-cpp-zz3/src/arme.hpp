#pragma once

#include "item.hpp"
#include "enchantement.hpp"
#include <exception>

class Arme : public Item
{
private:
    int durable;
    Enchantement *enchantement;

public:
    class DestroyedItemException : std::exception
    {
    private:
        std::string msg;

    public:
        explicit DestroyedItemException(const std::string &msg) : msg(msg) {}
        const char *what() const noexcept override { return msg.c_str(); }
    };

    Arme(std::string nom, int prix, int dura) : Item(nom, prix), durable(dura), enchantement(nullptr) {}
    Arme(std::string nom) : Item(nom), durable(0) {}
    Arme(Arme &a) : Item(a.Item::getNom(), a.getPrix()), durable(a.durable), enchantement(a.enchantement == nullptr ? nullptr : new Enchantement(*a.enchantement)) {}
    Arme(Arme &&a) noexcept : Item(a.Item::getNom(), a.getPrix()), durable(a.durable), enchantement(a.enchantement == nullptr ? nullptr : std::move(a.enchantement))
    {
        a.enchantement = nullptr;
        a.durable = 0;
    }
    inline std::string getNom() const { return Item::getNom() + " [" + std::to_string(durable) + "]"; }
    inline void utiliser()
    {
        if (durable == 0)
        {
            throw DestroyedItemException("");
        }
        else
        {
            --durable;
        }
    }
    inline Enchantement *getEnchantement() const { return enchantement; }
    inline void enchanter(Enchantement *enchanter)
    {
        if (enchantement)
        {
            delete enchantement;
        }
        enchantement = enchanter;
    }

    Arme &operator=(Arme &&a) noexcept
    {
        if (this == &a)
        {
            return *this;
        }
        delete enchantement;
        Item::operator=(std::move(a));
        durable = a.durable;
        enchantement = a.enchantement;
        a.enchantement = nullptr;
        a.durable = 0;
        return *this;
    }
    std::string getType() const override { return "Arme"; }
};
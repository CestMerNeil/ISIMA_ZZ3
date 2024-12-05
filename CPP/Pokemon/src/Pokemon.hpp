#ifndef POKEMON_HPP
#define POKEMON_HPP

#include <string>

class Pokemon
{
private:
    std::string name;
    int level;
    int hp;
    int attack;

public:
    Pokemon(std::string name, int level, int hp, int attack) : name(name), level(level), hp(hp), attack(attack) {}
    inline std::string getName() { return name; }
    inline int getLevel() { return level; }
    inline int getHp() { return hp; }
    inline int getAttack() { return attack; }
    void takeDamage(int attack)
    {
        if (attack >= hp)
        {
            hp = 0;
        }
        else
        {
            hp -= attack;
        }
    }
};

#endif
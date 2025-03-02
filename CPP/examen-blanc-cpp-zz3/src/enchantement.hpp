#pragma once

class Enchantement
{
private:
    float puissance;

public:
    Enchantement(float puissance) : puissance(puissance) {}
    inline float getPuissance() { return puissance; }
};
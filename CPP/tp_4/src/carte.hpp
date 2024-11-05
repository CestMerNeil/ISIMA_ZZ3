#ifndef CARTE
#define CARTE

class Carte
{
public:
    Carte(int v) : valeur(v) {};
    Carte(const Carte &) = delete;
    Carte &operator=(const Carte &) = delete;
    int getValeur() { return valeur; }

private:
    int valeur;
};

#endif
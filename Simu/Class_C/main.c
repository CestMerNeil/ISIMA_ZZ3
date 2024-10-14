#include "PointGraphique.h"

int main()
{
    PointGraphique *pg1 = creerPointGraphique(1, 2);
    PointGraphique *pg2 = creerPointGraphique(3, 4);
    printf("pg1: (%d, %d)\n", getX(pg1), getY(pg1));
    printf("pg2: (%d, %d)\n", getX(pg2), getY(pg2));
    printf("Nombre de points graphiques: %d\n", getNbPointsGraphiques());
    return 0;
}
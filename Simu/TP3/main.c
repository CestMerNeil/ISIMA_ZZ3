#include "ObjetGraphique.h"

int main()
{
    ObjetGraphique *og1 = creerObjetGraphique(1, 2);
    ObjetGraphique *og2 = creerObjetGraphique(3, 4);

    Cercle *c1 = creerCercle(5, 6, 7);
    Cercle *c2 = creerCercle(8, 9, 10);

    Rectangle *r1 = creerRectangle(11, 12, 13, 14);
    Rectangle *r2 = creerRectangle(15, 16, 17, 18);

    printf("og1: (%d, %d)\n", getX(og1), getY(og1));
    printf("og2: (%d, %d)\n", getX(og2), getY(og2));
    printf("Nombre d'objets graphiques: %d\n", getNbObjetsGraphiques());

    printf("c1: (%d, %d), rayon: %d\n", getX(c1->og), getY(c1->og), getRayon(c1));
    printf("c2: (%d, %d), rayon: %d\n", getX(c2->og), getY(c2->og), getRayon(c2));

    printf("r1: (%d, %d), largeur: %d, hauteur: %d\n", getX(r1->og), getY(r1->og), getLargeur(r1), getHauteur(r1));
    printf("r2: (%d, %d), largeur: %d, hauteur: %d\n", getX(r2->og), getY(r2->og), getLargeur(r2), getHauteur(r2));

    printf("Nombre d'objets graphiques: %d\n", getNbObjetsGraphiques());
    free(og1);
    free(og2);
    free(c1->og);
    free(c1);
    free(c2->og);
    free(c2);
    free(r1->og);
    free(r1);
    free(r2->og);
    free(r2);

    return 0;

    // gcc -Wall -Wextra -Werror -o main main.c ObjetGraphique.c
}
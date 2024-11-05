#ifndef OBJETGRAPHIQUE_H
#define OBJETGRAPHIQUE_H

#include <stdio.h>
#include <stdlib.h>

// ObjetGraphique 结构体定义
typedef struct ObjetGraphique
{
    int x;
    int y;
    int id;
} ObjetGraphique;

// Cercle 结构体定义
typedef struct Cercle
{
    ObjetGraphique *og;
    int radius;
} Cercle;

// Rectangle 结构体定义
typedef struct Rectangle
{
    ObjetGraphique *og;
    int largeur;
    int hauteur;
} Rectangle;

// 函数声明
void setX(ObjetGraphique *this, int x);
void setY(ObjetGraphique *this, int y);
int getX(ObjetGraphique *this);
int getY(ObjetGraphique *this);
int getNbObjetsGraphiques();
ObjetGraphique *creerObjetGraphique(int x, int y);

void setRayon(Cercle *this, int radius);
int getRayon(Cercle *this);
Cercle *creerCercle(int x, int y, int radius);

void setLargeur(Rectangle *this, int largeur);
void setHauteur(Rectangle *this, int hauteur);
int getLargeur(Rectangle *this);
int getHauteur(Rectangle *this);
Rectangle *creerRectangle(int x, int y, int largeur, int hauteur);

#endif // OBJETGRAPHIQUE_H

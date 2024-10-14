#ifndef POINTGRAPHIQUE_H
#define POINTGRAPHIQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PointGraphique PointGraphique;

void setX(PointGraphique *this, int x);
void setY(PointGraphique *this, int y);
int getX(PointGraphique *this);
int getY(PointGraphique *this);
int getNbPointsGraphiques();
PointGraphique *creerPointGraphique(int x, int y);

#endif
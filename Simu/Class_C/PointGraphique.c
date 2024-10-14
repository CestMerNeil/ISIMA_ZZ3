#include "PointGraphique.h"

struct PointGraphique
{
    /* data */
    int x;
    int y;
    int id;
};

static int globalId = 0;

int getNbPointsGraphiques()
{
    return globalId;
}

PointGraphique *creerPointGraphique(int x, int y)
{
    PointGraphique *pg = (PointGraphique *)malloc(sizeof(PointGraphique));
    pg->x = x;
    pg->y = y;
    pg->id = globalId++;
    return pg;
}

void setX(PointGraphique *this, int x)
{
    this->x = x;
}

void setY(PointGraphique *this, int y)
{
    this->y = y;
}

int getX(PointGraphique *this)
{
    return this->x;
}

int getY(PointGraphique *this)
{
    return this->y;
}
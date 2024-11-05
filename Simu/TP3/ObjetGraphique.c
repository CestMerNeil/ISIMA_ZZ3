#include "ObjetGraphique.h"

static int globalId = 0;

int getNbObjetsGraphiques()
{
    return globalId;
};

ObjetGraphique *creerObjetGraphique(int x, int y)
{
    ObjetGraphique *og = (ObjetGraphique *)malloc(sizeof(ObjetGraphique));
    og->x = x;
    og->y = y;
    og->id = globalId++;
    return og;
}

void setX(ObjetGraphique *this, int x)
{
    this->x = x;
}

void setY(ObjetGraphique *this, int y)
{
    this->y = y;
}

int getX(ObjetGraphique *this)
{
    return this->x;
}

int getY(ObjetGraphique *this)
{
    return this->y;
}

void setRayon(Cercle *this, int radius)
{
    this->radius = radius;
}

int getRayon(Cercle *this)
{
    return this->radius;
}

Cercle *creerCercle(int x, int y, int radius)
{
    Cercle *c = (Cercle *)malloc(sizeof(Cercle));
    c->og = creerObjetGraphique(x, y);
    c->radius = radius;
    return c;
}

void setLargeur(Rectangle *this, int largeur)
{
    this->largeur = largeur;
}

void setHauteur(Rectangle *this, int hauteur)
{
    this->hauteur = hauteur;
}

int getLargeur(Rectangle *this)
{
    return this->largeur;
}

int getHauteur(Rectangle *this)
{
    return this->hauteur;
}

Rectangle *creerRectangle(int x, int y, int largeur, int hauteur)
{
    Rectangle *r = (Rectangle *)malloc(sizeof(Rectangle));
    r->og = creerObjetGraphique(x, y);
    r->largeur = largeur;
    r->hauteur = hauteur;
    return r;
}

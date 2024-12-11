// Entetes //---------------------------------------------------------------------------------------
#include <vecteur.hpp>

// Implementation  V e c t e u r //-----------------------------------------------------------------

//--------------------------------------------------------------------------------------------Copier
void Vecteur::copier(const Vecteur & v) {
 if (capacite_<v.taille_) {
  if (elements_) delete[] elements_;
  capacite_=v.taille_;
  elements_=new int[capacite_];
 }

 taille_=v.taille_;
 for (unsigned i = 0; i<taille_; ++i) elements_[i]=v.elements_[i];
}

//-------------------------------------------------------------------------------------------Ajouter
void Vecteur::ajouter(int e) {
 if (taille_==capacite_) {
  int * tab = new int[2*capacite_];
  for (unsigned i = 0; i<taille_; ++i) tab[i]=elements_[i];
  if (elements_) delete[] elements_;
  elements_=tab;
  capacite_*=2;
 }

 elements_[taille_++]=e;
}

// Implementation fonctions //----------------------------------------------------------------------

//--------------------------------------------------------------------------------------Operateur <<
std::ostream & operator<<(std::ostream & flux,const Vecteur & v) {
 // Boucle sans iterateur
 // for (unsigned i = 0; i<v.getTaille(); ++i) flux << v[i] << " ";

 // Boucle avec iterateur (a l'ancienne)
 // for (Iterateur i = v.begin(); i!=v.end(); ++i) flux << *i << " ";

 // Boucle avec iterateur (C++ moderne)
 for (int x : v) flux << x << " ";

 return flux;
}

//-------------------------------------------------------------------------------------- Operateur +
Vecteur operator+(const Vecteur & v1,const Vecteur & v2) {
 Vecteur v3(v1.getTaille()+v2.getTaille());

 v3=v1;
 for (unsigned i = 0; i<v2.getTaille(); ++i) v3.ajouter(v2[i]);

 return v3;
}

//---------------------------------------------------------------------------------------Operateur *
int operator*(const Vecteur & v1,const Vecteur & v2) {
 int r = 0;

 if (v1.getTaille()!=v2.getTaille()) throw std::string("Erreur produit scalaire");
 for (unsigned i = 0; i<v1.getTaille(); ++i) r+=v1[i]*v2[i];

 return r;
}

// Fin //-------------------------------------------------------------------------------------------

// Gardien //---------------------------------------------------------------------------------------
#ifndef VECTEUR_HPP_e2de9d8bffa542748c65a181aaf7a778
#define VECTEUR_HPP_e2de9d8bffa542748c65a181aaf7a778

// Entetes //---------------------------------------------------------------------------------------
#include <complexe.hpp>
#include <stdexcept>

// Classe  V e c t e u r //-------------------------------------------------------------------------
class Vecteur {
 //----------------------------------------------------------------------------------------Attributs
 private:
  unsigned     taille_;
  complexe_t * tableau_;

 //---------------------------------------------------------------------------------------Accesseurs
 public:
  unsigned getTaille() const { return taille_; }

  complexe_t & operator[](unsigned i) {
   if (i<taille_) return tableau_[i];
   throw std::out_of_range("");
  }

  const complexe_t & operator[](unsigned i) const {
   if (i<taille_) return tableau_[i];
   throw std::out_of_range("");
  }

 public:
  //-----------------------------------------------------------------------------Constructeur defaut
  explicit Vecteur(unsigned t = 10) : taille_(t),tableau_(new complexe_t[taille_]) {}

  //------------------------------------------------------------------------------Constructeur copie
  Vecteur(const Vecteur & v) : taille_(v.taille_),tableau_(new complexe_t[taille_]) {
   for (unsigned i = 0; i<taille_; ++i) tableau_[i]=v[i];
  }

  //-------------------------------------------------------------------------------------Destructeur
  ~Vecteur() { if (tableau_) delete[] tableau_; }

  //-------------------------------------------------------------------------------Affectation copie
  Vecteur & operator=(const Vecteur & v) {
   if (this!=&v) {
    if (taille_!=v.taille_) throw std::length_error("");
    for (unsigned i = 0; i<v.taille_; ++i) tableau_[i]=v[i];
   }

   return *this;
  }
};

// Surcharge operateurs //--------------------------------------------------------------------------

//--------------------------------------------------------------------------------------Operateur <<
inline std::ostream & operator<<(std::ostream & flux,const Vecteur & v) {
 for (unsigned i = 0; i<v.getTaille(); ++i) flux << v[i] << " ";
 return flux;
}

//---------------------------------------------------------------------------------------Operateur +
inline Vecteur operator+(const Vecteur & v1,const Vecteur & v2) {
 Vecteur v;

 for (unsigned i = 0; i<v1.getTaille(); ++i) v[i]=v1[i]+v2[i];

 return v;
}

//---------------------------------------------------------------------------------------Operateur *
inline Vecteur operator*(const Vecteur & v1,const Vecteur & v2) {
 Vecteur v;

 for (unsigned i = 0; i<v1.getTaille(); ++i) v[i]=v1[i]*v2[i];

 return v;
}

// Fin //-------------------------------------------------------------------------------------------
#endif

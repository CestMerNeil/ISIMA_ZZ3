// Gardien //---------------------------------------------------------------------------------------
#ifndef CLASSE_HPP_e2de9d8bffa542748c65a181aaf7a778
#define CLASSE_HPP_e2de9d8bffa542748c65a181aaf7a778

// Entetes //---------------------------------------------------------------------------------------
#include <iostream>

// Classe  C l a s s e //---------------------------------------------------------------------------
class Classe {
 //----------------------------------------------------------------------------------------Attributs
 private:
  double   borneInf_;
  double   borneSup_;
  unsigned quantite_;
 //---------------------------------------------------------------------------------------Accesseurs
 public:
  double   getBorneInf() const { return borneInf_; }
  double   getBorneSup() const { return borneSup_; }
  unsigned getQuantite() const { return quantite_; }

  void setBorneInf(double borne) { borneInf_=borne; }
  void setBorneSup(double borne) { borneSup_=borne; }
  void setQuantite(unsigned quantite) { quantite_=quantite; }
 //------------------------------------------------------------------------------------Constructeurs
 public:
  Classe(double borneInf = 0.0,double borneSup = 0.0)
  : borneInf_(borneInf),borneSup_(borneSup),quantite_(0) {}
 //-------------------------------------------------------------------------------Methodes publiques
 public:
  void ajouter() { ++quantite_; }
};

// Fonctions inline //------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------Operateur <
inline bool operator<(const Classe & classe1,const Classe & classe2) {
 return (classe1.getBorneInf() < classe2.getBorneInf());
}

//---------------------------------------------------------------------------------------Operateur >
inline bool operator>(const Classe & classe1,const Classe & classe2) {
 return (classe2<classe1);
}

//--------------------------------------------------------------------------------------Operateur <<
inline std::ostream & operator<<(std::ostream & flux,const Classe & classe) {
 flux << "[" << classe.getBorneInf() << ";" << classe.getBorneSup() << "]";
 return flux;
}

// Fin //-------------------------------------------------------------------------------------------
#endif

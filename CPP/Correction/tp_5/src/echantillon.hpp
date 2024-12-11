// Gardien //---------------------------------------------------------------------------------------
#ifndef ECHANTILLON_HPP_e2de9d8bffa542748c65a181aaf7a778
#define ECHANTILLON_HPP_e2de9d8bffa542748c65a181aaf7a778

// Entetes //---------------------------------------------------------------------------------------
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <valeur.hpp>

// Classe  E c h a n t i l l o n //-----------------------------------------------------------------
class Echantillon {
 //--------------------------------------------------------------------------------------------Types
 public:
  using value_type = Valeur; // Necessaire pour la derniere question
 //----------------------------------------------------------------------------------------Attributs
 private:
  std::vector<Valeur> valeurs_;
 //---------------------------------------------------------------------------------------Accesseurs
 public:
  unsigned getTaille() const { return valeurs_.size(); }

  const Valeur & getValeur(unsigned indice) const {
   if (indice<valeurs_.size()) return valeurs_[indice];
   else throw std::out_of_range("Echantillon::getValeur()");
  }
 //-------------------------------------------------------------------------------Methodes publiques
 public:
  void ajouter(const Valeur & valeur) { valeurs_.push_back(valeur); }

  void push_back(const Valeur & valeur) { ajouter(valeur); } // Necessaire pour la derniere question

  const Valeur & getMinimum() const {
   if (valeurs_.size()!=0) {
    auto min = std::min_element(valeurs_.begin(),valeurs_.end(), // auto = std::vector<Valeur>::const_iterator
                                [] (const Valeur & a,const Valeur & b) {
                                 return a.getNombre() < b.getNombre();
                                }
                               );

    return *min;
   }
   else throw std::domain_error("Echantillon::getMinimum()");
  }

  const Valeur & getMaximum() const {
   if (valeurs_.size()!=0) {
    auto max = std::max_element(valeurs_.begin(),valeurs_.end(), // auto = std::vector<Valeur>::const_iterator
                                [] (const Valeur & a,const Valeur & b) {
                                 return a.getNombre() < b.getNombre();
                                }
                               );

    return *max;
   }
   else throw std::domain_error("Echantillon::getMaximum()");
  }
};

// Fonctions inline //------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------Operateur <<
inline std::ostream & operator<<(std::ostream & flux,const Echantillon & echantillon) {
 for (unsigned i = 0; i<echantillon.getTaille(); ++i)
  flux << echantillon.getValeur(i) << " ";

 return flux;
}

// Fin //-------------------------------------------------------------------------------------------
#endif

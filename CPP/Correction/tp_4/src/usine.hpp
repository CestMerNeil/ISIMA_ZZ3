// Gardien //---------------------------------------------------------------------------------------
#ifndef USINE_HPP_e2de9d8bffa542748c65a181aaf7a778
#define USINE_HPP_e2de9d8bffa542748c65a181aaf7a778

// Entetes //---------------------------------------------------------------------------------------
#include <memory>
#include <carte.hpp>

// Classe  U s i n e C a r t e //-------------------------------------------------------------------
class UsineCarte {
 //----------------------------------------------------------------------------------------Attributs
 private:
  unsigned compteur_;
  unsigned max_;

 //---------------------------------------------------------------------Constructeurs & Affectations
 public:
  UsineCarte(unsigned max = 52) : compteur_(0),max_(max) {}

  UsineCarte(const UsineCarte &) = delete;

  UsineCarte & operator=(const UsineCarte &) = delete;

 //-------------------------------------------------------------------------------Methodes publiques
 public:
  std::unique_ptr<Carte> getCarte();
};

// Fin //-------------------------------------------------------------------------------------------
#endif

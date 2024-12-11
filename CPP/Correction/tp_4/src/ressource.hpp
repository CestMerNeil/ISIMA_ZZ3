// Gardien //---------------------------------------------------------------------------------------
#ifndef RESSOURCE_HPP_e2de9d8bffa542748c65a181aaf7a778
#define RESSOURCE_HPP_e2de9d8bffa542748c65a181aaf7a778

// Entetes //---------------------------------------------------------------------------------------
#include <iostream>
#include <memory>
#include <vector>

// Classe  R e s s o u r c e //---------------------------------------------------------------------
class Ressource {
 //----------------------------------------------------------------------------------------Attributs
 private:
  unsigned stock_;

 //---------------------------------------------------------------------------------------Accesseurs
 public:
  unsigned getStock() const { return stock_; }

 //------------------------------------------------------------------------------------Constructeurs
 public:
  Ressource(unsigned stock) : stock_(stock) {}

 //-------------------------------------------------------------------------------Methodes publiques
 public:
  void consommer(unsigned quantite) { stock_ = (stock_<quantite ? 0 : stock_-quantite); }
};

// Declarations types //----------------------------------------------------------------------------
using ressources_t = std::vector<std::weak_ptr<Ressource>>;

// Declarations fonctions //------------------------------------------------------------------------
std::ostream & operator<<(std::ostream &,const ressources_t &);

// Fin //-------------------------------------------------------------------------------------------
#endif

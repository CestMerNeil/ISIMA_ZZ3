// Gardien //---------------------------------------------------------------------------------------
#ifndef COMPARATEUR_HPP_e2de9d8bffa542748c65a181aaf7a778
#define COMPARATEUR_HPP_e2de9d8bffa542748c65a181aaf7a778

// Entetes //---------------------------------------------------------------------------------------
#include <classe.hpp>

// Classe  C o m p a r a t e u r Q u a n t i t e //-------------------------------------------------
struct ComparateurQuantite {
 //-------------------------------------------------------------------------------------Operateur ()
 bool operator()(const Classe & a,const Classe & b) const {
  return (a.getQuantite()==b.getQuantite() ? a<b : a.getQuantite()>b.getQuantite());
 }
};

// Fin //-------------------------------------------------------------------------------------------
#endif

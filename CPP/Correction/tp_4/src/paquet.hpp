// Gardien //---------------------------------------------------------------------------------------
#ifndef PAQUET_HPP_e2de9d8bffa542748c65a181aaf7a778
#define PAQUET_HPP_e2de9d8bffa542748c65a181aaf7a778

// Entetes //---------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <usine.hpp>

// Declarations types //----------------------------------------------------------------------------
using paquet_t = std::vector<std::unique_ptr<Carte>>;

// Declarations fonctions //------------------------------------------------------------------------
void remplir(paquet_t &,UsineCarte &);

std::ostream & operator<<(std::ostream &,const paquet_t &);

// Fin //-------------------------------------------------------------------------------------------
#endif

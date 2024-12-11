// Gardien //---------------------------------------------------------------------------------------
#ifndef EXPONENTIELLE_HPP_e2de9d8bffa542748c65a181aaf7a778
#define EXPONENTIELLE_HPP_e2de9d8bffa542748c65a181aaf7a778

// Entetes //---------------------------------------------------------------------------------------
#include <factorielle.hpp>
#include <puissance.hpp>

// Classe  E x p o n e n t i e l l e //-------------------------------------------------------------
template <int N> struct Exponentielle {
 static double valeur(double x)
 { return (Puissance<N>::valeur(x)/Factorielle<N>::valeur + Exponentielle<N-1>::valeur(x)); }
};

template <> struct Exponentielle<0> {
 static double valeur(double) { return 1; }
};

// Fin //-------------------------------------------------------------------------------------------
#endif

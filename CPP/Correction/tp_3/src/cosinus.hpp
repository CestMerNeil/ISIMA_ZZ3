// Gardien //---------------------------------------------------------------------------------------
#ifndef COSINUS_HPP_e2de9d8bffa542748c65a181aaf7a778
#define COSINUS_HPP_e2de9d8bffa542748c65a181aaf7a778

// Entetes //---------------------------------------------------------------------------------------
#include <factorielle.hpp>
#include <puissance.hpp>

// Classe  C o s i n u s //-------------------------------------------------------------------------
template <int N> struct Cosinus {
 static double valeur(double x) {
  return (Puissance<N>::valeur(-1)*Puissance<2*N>::valeur(x)/Factorielle<2*N>::valeur
          + Cosinus<N-1>::valeur(x));
 }
};

template <> struct Cosinus<0> {
 static double valeur(double) { return 1; }
};

// Classe  S i n u s //-----------------------------------------------------------------------------
template <int N> struct Sinus {
 static double valeur(double x) {
  return (Puissance<N>::valeur(-1)*Puissance<2*N+1>::valeur(x)/Factorielle<2*N+1>::valeur
          + Sinus<N-1>::valeur(x));
 }
};

template <> struct Sinus<0> {
 static double valeur(double x) { return x; }
};

// Fin //-------------------------------------------------------------------------------------------
#endif

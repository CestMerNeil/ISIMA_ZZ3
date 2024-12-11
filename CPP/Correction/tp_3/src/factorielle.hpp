// Gardien //---------------------------------------------------------------------------------------
#ifndef FACTORIELLE_HPP_e2de9d8bffa542748c65a181aaf7a778
#define FACTORIELLE_HPP_e2de9d8bffa542748c65a181aaf7a778

// Classe  F a c t o r i e l l e //-----------------------------------------------------------------
template <int N> struct Factorielle {
 static const unsigned long valeur = N*Factorielle<N-1>::valeur;
};

template <> struct Factorielle<0> {
 static const unsigned long valeur = 1;
};

// Fonctions //-------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------Factorielle
template <int N> inline unsigned long factorielle(void) { return (factorielle<N-1>()*N); }
template <> inline unsigned long factorielle<0>(void) { return 1; }

// Fin //-------------------------------------------------------------------------------------------
#endif

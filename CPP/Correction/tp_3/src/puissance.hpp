// Gardien //---------------------------------------------------------------------------------------
#ifndef PUISSANCE_HPP_e2de9d8bffa542748c65a181aaf7a778
#define PUISSANCE_HPP_e2de9d8bffa542748c65a181aaf7a778

// Classe  P u i s s a n c e //---------------------------------------------------------------------
template <int N> struct Puissance {
 static double valeur(double x) { return x*Puissance<N-1>::valeur(x); }
};

template <> struct Puissance<0> {
 static double valeur(double) { return 1; }
};

// Fin //-------------------------------------------------------------------------------------------
#endif

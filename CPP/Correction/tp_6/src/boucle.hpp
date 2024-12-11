// Gardien //---------------------------------------------------------------------------------------
#ifndef BOUCLE_HPP_e2de9d8bffa542748c65a181aaf7a778
#define BOUCLE_HPP_e2de9d8bffa542748c65a181aaf7a778

// Entetes //---------------------------------------------------------------------------------------
#include <thread>

// Fonctions inline //------------------------------------------------------------------------------

//------------------------------------------------------------------------------------for_sequentiel
template <typename C>
inline void for_sequentiel(unsigned x,unsigned y,const C & callable) {
 for (unsigned i = x; i<y; ++i) callable(i);
}

//-------------------------------------------------------------------------------------for_parallele
template <unsigned N,typename C>
inline void for_parallele(unsigned x,unsigned y,const C & callable) {
 unsigned    debut;
 unsigned    fin;
 std::thread threads[N-1];

 for (unsigned k = 0; k<N-1; ++k) {
  debut = x + k*(y-x)/N;
  fin = x + (k+1)*(y-x)/N;
  threads[k] = std::thread(for_sequentiel<C>,debut,fin,callable);
 }

 debut = x + (N-1)*(y-x)/N;
 for_sequentiel(debut,y,callable);

 for (unsigned k = 0; k<N-1; ++k) threads[k].join();
}

// Fin //-------------------------------------------------------------------------------------------
#endif

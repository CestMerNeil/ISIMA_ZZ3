// Entetes //---------------------------------------------------------------------------------------
#include <mutex>
#include <boucle.hpp>
#include <nombre.hpp>

// Variables globales //----------------------------------------------------------------------------
std::mutex mutex;

unsigned compteur = 0;

// Synchronisation avec mutex //--------------------------------------------------------------------

//-----------------------------------------------------------------------------------Version directe
inline unsigned incrementerCompteur_v1() {
 unsigned retour;

 mutex.lock();
 retour=++compteur;
 mutex.unlock();

 return retour;
}

//-------------------------------------------------------------------------------Version avec verrou
inline unsigned incrementerCompteur_v2() {
 std::lock_guard<std::mutex> verrou(mutex);
 return ++compteur;
}

// Fonction principale //---------------------------------------------------------------------------
int main() {
 const unsigned taille = 24;

 std::vector<Nombre> a(taille);
 std::vector<Nombre> b(taille);
 std::vector<Nombre> c(taille);

 // for_sequentiel(0,taille,[&] (unsigned i) { a[i] = ++compteur; });
 // for_sequentiel(0,taille,[&] (unsigned i) { b[i] = ++compteur; });

 // for_parallele<4>(0,taille,[&] (unsigned i) { a[i] = ++compteur; });
 // for_parallele<4>(0,taille,[&] (unsigned i) { b[i] = ++compteur; });

 for_parallele<4>(0,taille,[&] (unsigned i) { a[i] = incrementerCompteur_v2(); });
 for_parallele<4>(0,taille,[&] (unsigned i) { b[i] = incrementerCompteur_v2(); });

 std::cout << "a = " << a << std::endl;
 std::cout << "b = " << b << std::endl;
 std::cout << "compteur = " << compteur << std::endl;

 // for_sequentiel(0,taille,[&] (unsigned i) { c[i] = a[i]*b[i]; });
 for_parallele<4>(0,taille,[&] (unsigned i) { c[i] = a[i]*b[i]; });

 std::cout << "c = " << c << std::endl;

 return 0;
}

// Fin //-------------------------------------------------------------------------------------------

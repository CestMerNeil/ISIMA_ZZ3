// Entetes //---------------------------------------------------------------------------------------
#include <future>
#include <mutex>
#include <boucle.hpp>
#include <nombre.hpp>

// Variables globales //----------------------------------------------------------------------------
std::mutex mutex;

unsigned compteur = 0;

// Fonctions //-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------incrementerCompteur
inline unsigned incrementerCompteur() {
 std::lock_guard<std::mutex> verrou(mutex);
 return ++compteur;
}

// Fonction principale //---------------------------------------------------------------------------
int main() {
 const unsigned taille = 24;

 std::vector<Nombre> a(taille);
 std::vector<Nombre> b(taille);
 std::vector<Nombre> c(taille);
 std::vector<Nombre> d(taille);
 std::vector<Nombre> e(taille);
 std::vector<Nombre> f(taille);
 std::vector<Nombre> g(taille);

 // for_sequentiel(0,taille,[&] (unsigned i) { a[i] = ++compteur; });
 // for_sequentiel(0,taille,[&] (unsigned i) { b[i] = ++compteur; });
 // for_sequentiel(0,taille,[&] (unsigned i) { c[i] = ++compteur; });
 // for_sequentiel(0,taille,[&] (unsigned i) { d[i] = ++compteur; });
 // for_sequentiel(0,taille,[&] (unsigned i) { e[i] = ++compteur; });
 // for_sequentiel(0,taille,[&] (unsigned i) { f[i] = ++compteur; });

 // for_parallele<6>(0,taille,[&] (unsigned i) { a[i] = incrementerCompteur(); });
 // for_parallele<6>(0,taille,[&] (unsigned i) { b[i] = incrementerCompteur(); });
 // for_parallele<6>(0,taille,[&] (unsigned i) { c[i] = incrementerCompteur(); });
 // for_parallele<6>(0,taille,[&] (unsigned i) { d[i] = incrementerCompteur(); });
 // for_parallele<6>(0,taille,[&] (unsigned i) { e[i] = incrementerCompteur(); });
 // for_parallele<6>(0,taille,[&] (unsigned i) { f[i] = incrementerCompteur(); });

 std::future<void> futurs[5];

 futurs[0] = std::async(std::launch::async,[&] () {
  for_sequentiel(0,taille,[&] (unsigned i) { a[i] = incrementerCompteur(); });
 });

 futurs[1] = std::async(std::launch::async,[&] () {
  for_sequentiel(0,taille,[&] (unsigned i) { b[i] = incrementerCompteur(); });
 });

 futurs[2] = std::async(std::launch::async,[&] () {
  for_sequentiel(0,taille,[&] (unsigned i) { c[i] = incrementerCompteur(); });
 });

 futurs[3] = std::async(std::launch::async,[&] () {
  for_sequentiel(0,taille,[&] (unsigned i) { d[i] = incrementerCompteur(); });
 });

 futurs[4] = std::async(std::launch::async,[&] () {
  for_sequentiel(0,taille,[&] (unsigned i) { e[i] = incrementerCompteur(); });
 });

 for_sequentiel(0,taille,[&] (unsigned i) { f[i] = incrementerCompteur(); });

 for (unsigned i = 0; i<5; ++i) futurs[i].wait();

 std::cout << "a = " << a << std::endl;
 std::cout << "b = " << b << std::endl;
 std::cout << "c = " << c << std::endl;
 std::cout << "d = " << d << std::endl;
 std::cout << "e = " << e << std::endl;
 std::cout << "f = " << f << std::endl;
 std::cout << "compteur = " << compteur << std::endl;

 // for_sequentiel(0,taille,[&] (unsigned i) { g[i] = a[i]*b[i] + c[i]/d[i] - e[i]*f[i]; });
 // for_parallele<6>(0,taille,[&] (unsigned i) { g[i] = a[i]*b[i] + c[i]/d[i] - e[i]*f[i]; });

 futurs[0] = std::async(std::launch::async, [&]() {
  for_parallele<2>(0,taille, [&](unsigned i) { a[i] = a[i]*b[i]; } );
 });

 futurs[1] = std::async(std::launch::async, [&]() {
  for_parallele<2>(0,taille, [&](unsigned i) { c[i] = c[i]/d[i]; } );
 });

 for_parallele<2>(0,taille, [&](unsigned i) { e[i] = e[i]*f[i]; } );

 for (unsigned i = 0; i<2; ++i) futurs[i].wait();

 for_parallele<6>(0,taille, [&](unsigned i) { g[i] = a[i] + c[i] - e[i]; } );

 std::cout << "g = " << g << std::endl;

 return 0;
}

// Fin //-------------------------------------------------------------------------------------------

// Entetes //---------------------------------------------------------------------------------------
#include <ressource.hpp>

// Fonctions //-------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------Operateur <<
std::ostream & operator<<(std::ostream & flux,const ressources_t & ressources) {
 for (const std::weak_ptr<Ressource> & ressource : ressources) {
  auto p = ressource.lock(); // auto = std::shared_ptr<Ressource>
  if (p)
   flux << p->getStock() << " ";
  else
   flux << "- ";
 }

 return flux;
}

// Fin //-------------------------------------------------------------------------------------------

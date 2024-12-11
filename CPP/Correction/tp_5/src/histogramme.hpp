// Gardien //---------------------------------------------------------------------------------------
#ifndef HISTOGRAMME_HPP_e2de9d8bffa542748c65a181aaf7a778
#define HISTOGRAMME_HPP_e2de9d8bffa542748c65a181aaf7a778

// Entetes //---------------------------------------------------------------------------------------
#include <iostream>
#include <map>
#include <set>
#include <classe.hpp>
#include <echantillon.hpp>

// Classe  H i s t o g r a m m e //-----------------------------------------------------------------
template <typename COMPARATEUR = std::less<Classe>>
class Histogramme
{
  //--------------------------------------------------------------------------------------------Types
public:
  // using classes_t = std::vector<Classe>;
  using classes_t = std::set<Classe, COMPARATEUR>;
  using valeurs_t = std::multimap<Classe, Valeur>;
  //----------------------------------------------------------------------------------------Attributs
private:
  double borneInf_;
  double borneSup_;
  classes_t classes_;
  valeurs_t valeurs_;
  //---------------------------------------------------------------------------------------Accesseurs
public:
  double getBorneInf() const { return borneInf_; }
  double getBorneSup() const { return borneSup_; }

  const classes_t &getClasses() const { return classes_; }
  const valeurs_t &getValeurs() const { return valeurs_; }

  auto getValeurs(const Classe &classe) const // auto = std::pair<valeurs_t::const_iterator,
  {
    return valeurs_.equal_range(classe);
  } //                  valeurs_t::const_iterator>
  //------------------------------------------------------------------------------------Constructeurs
public:
  Histogramme(double borneInf, double borneSup, unsigned nbClasse);

  template <typename COMPARATEUR2>
  Histogramme(const Histogramme<COMPARATEUR2> &);
  //-------------------------------------------------------------------------------Methodes publiques
public:
  void ajouter(const Valeur &);
  void ajouter(const Echantillon &);
};

// Implementation  H i s t o g r a m m e //---------------------------------------------------------

//--------------------------------------------------------------Constructeur(double,double,unsigned)
template <typename COMPARATEUR>
Histogramme<COMPARATEUR>::Histogramme(double borneInf, double borneSup, unsigned nbClasse)
    : borneInf_(borneInf), borneSup_(borneSup)
{
  double intervalle = (borneSup_ - borneInf_) / nbClasse;

  for (unsigned i = 0; i < nbClasse; ++i)
    classes_.insert(Classe(borneInf_ + intervalle * i, borneInf_ + intervalle * (i + 1)));
}

//-----------------------------------------------------------Constructeur(Histogramme<COMPARATEUR2>)
template <typename COMPARATEUR>
template <typename COMPARATEUR2>
Histogramme<COMPARATEUR>::Histogramme(const Histogramme<COMPARATEUR2> &histo)
    : borneInf_(histo.getBorneInf()), borneSup_(histo.getBorneSup())
{
  // Boucle a l'ancienne
  // auto it = histo.getClasses().begin(); // auto = Histogramme<COMPARATEUR2>::classes_t::const_iterator
  // while (it!=histo.getClasses().end()) classes_.insert(*(it++));

  // Boucle C++ moderne
  // for (const Classe & classe : histo.getClasses()) classes_.insert(classe);

  // Insertion directe
  classes_.insert(histo.getClasses().begin(), histo.getClasses().end());

  valeurs_.insert(histo.getValeurs().begin(), histo.getValeurs().end());
}

//-----------------------------------------------------------------------------------Ajouter(Valeur)
template <typename COMPARATEUR>
void Histogramme<COMPARATEUR>::ajouter(const Valeur &valeur)
{
  // Recherche avec iterateurs
  // auto it = classes_.begin(); // auto = classes_t::const_iterator
  //
  // while (it != classes_.end()) {
  //  if (valeur.getNombre() >= it->getBorneInf() && valeur.getNombre() < it->getBorneSup()) break;
  //  ++it;
  // }

  // Recherche avec "std::find_if"
  auto it = std::find_if(classes_.begin(), classes_.end(), // auto = classes_t::const_iterator
                         [&valeur](const Classe &c)
                         {
                           return (valeur.getNombre() >= c.getBorneInf() && valeur.getNombre() < c.getBorneSup());
                         });

  if (it != classes_.end())
  {
    Classe classe = *it;

    classe.ajouter();
    classes_.erase(it);
    classes_.insert(classe);

    valeurs_.insert(std::make_pair(classe, valeur));
  }

  // Solution possible pour un vecteur (concerne le debut de l'exercice uniquement)
  // for (Classe & classe : classes_) {
  //  if (valeur.getNombre() >= classe.getBorneInf() && valeur.getNombre() < classe.getBorneSup()) {
  //   classe.ajouter();
  //   break;
  //  }
  // }
}

//------------------------------------------------------------------------------Ajouter(Echantillon)
template <typename COMPARATEUR>
void Histogramme<COMPARATEUR>::ajouter(const Echantillon &echantillon)
{
  for (unsigned i = 0; i < echantillon.getTaille(); ++i)
    ajouter(echantillon.getValeur(i));
}

// Implementation fonctions //----------------------------------------------------------------------

//--------------------------------------------------------------------------------------Operateur <<
template <typename COMPARATEUR>
std::ostream &operator<<(std::ostream &flux, const Histogramme<COMPARATEUR> &histo)
{
  // Boucle a l'ancienne
  // using it_classes_t = typename Histogramme<COMPARATEUR>::classes_t::const_iterator;
  // using it_valeurs_t = typename Histogramme<COMPARATEUR>::valeurs_t::const_iterator;
  //
  // std::pair<it_valeurs_t,it_valeurs_t> intervalle;
  //
  // it_classes_t it = histo.getClasses().begin();
  //
  // while (it!=histo.getClasses().end()) {
  //  flux << *it << " = " << it->getQuantite() << " :";
  //  intervalle=histo.getValeurs(*it);
  //
  //  while (intervalle.first!=intervalle.second) {
  //   flux << " " << intervalle.first->second;
  //   ++(intervalle.first);
  //  }
  //
  //  flux << std::endl;
  //  ++it;
  // }

  // Boucle C++ moderne
  for (const Classe &classe : histo.getClasses())
  {
    flux << classe << " = " << classe.getQuantite() << " :";
    auto intervalle = histo.getValeurs(classe); // auto = std::pair<it_valeurs_t,it_valeurs_t>

    while (intervalle.first != intervalle.second)
    {
      flux << " " << intervalle.first->second;
      ++(intervalle.first);
    }

    flux << std::endl;
  }

  return flux;
}

// Fin //-------------------------------------------------------------------------------------------
#endif

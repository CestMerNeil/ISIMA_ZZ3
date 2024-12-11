// Gardien //---------------------------------------------------------------------------------------
#ifndef CARTE_HPP_e2de9d8bffa542748c65a181aaf7a778
#define CARTE_HPP_e2de9d8bffa542748c65a181aaf7a778

// Classe  C a r t e //-----------------------------------------------------------------------------
class Carte {
 //---------------------------------------------------------------------------------------------Amis
 friend class UsineCarte;

 //----------------------------------------------------------------------------------------Attributs
 private:
  unsigned valeur_;

  static unsigned compteur_;

 //---------------------------------------------------------------------------------------Accesseurs
 public:
  unsigned getValeur() const { return valeur_; }

  static unsigned getCompteur() { return compteur_; }

 //---------------------------------------------------------------------Constructeurs & Affectations
 private:
  Carte(unsigned valeur) : valeur_(valeur) { ++compteur_; }

 public:
  Carte(const Carte &) = delete;

  Carte & operator=(const Carte &) = delete;

 //--------------------------------------------------------------------------------------Destructeur
 public:
  ~Carte() { --compteur_; }
};

// Fin //-------------------------------------------------------------------------------------------
#endif

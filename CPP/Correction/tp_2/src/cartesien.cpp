// Entetes //---------------------------------------------------------------------------------------
#include <cmath>
#include <cartesien.hpp>
#include <polaire.hpp>

// Implementation  C a r t e s i e n //-------------------------------------------------------------

//--------------------------------------------------------------------------------------Constructeur
Cartesien::Cartesien(const Polaire & polaire) { polaire.convertir(*this); }

//------------------------------------------------------------------------------------------Afficher
void Cartesien::afficher(std::ostream & flux) const
{ flux << "(x=" << x_ << ";y=" << y_ << ")"; }

//-------------------------------------------------------------------------------------------Charger
void Cartesien::charger(std::istream & flux) {
 flux >> x_;
 flux >> y_;
}

//-----------------------------------------------------------------------------------------Convertir
void Cartesien::convertir(Cartesien & cartesien) const {
 cartesien.x_=x_;
 cartesien.y_=y_;
}

//-----------------------------------------------------------------------------------------Convertir
void Cartesien::convertir(Polaire & polaire) const {
 polaire.setAngle(std::atan2(y_,x_)*180/M_PI);
 polaire.setDistance(std::hypot(x_,y_));
}

// Fin //-------------------------------------------------------------------------------------------

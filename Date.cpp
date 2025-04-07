#include <algorithm>
#include <iostream>

#include "Date.h"

// constructeur

Date::Date(int annee, int mois, int jour)
    : d_annee{annee}, d_mois{mois}, d_jour{jour} {}

// getter

int Date::getAnnee() const { return d_annee; }

int Date::getMois() const { return d_mois; }

int Date::getJour() const { return d_jour; }

// setter

void Date::setAnnee(int annee) {
  if (annee > 2025 || annee < 2024) {
    std::cerr << "L'année n'est pas valide" << std::endl;
  } else {
    d_annee = annee;
  }
}

void Date::setMois(int mois) {
  int mois_dispo[] = {10, 11, 12, 1, 2};
  int x = sizeof(mois_dispo) / sizeof(*mois_dispo);

  // on vérifie si le mois en paramètre est oct, nov, dec, jan ou fev
  bool mois_present =
      std::find(mois_dispo, mois_dispo + x, mois) != mois_dispo + x;
  if (mois_present) {
    d_mois = mois;
  } else {
    std::cerr << "Le mois n'est pas valide" << std::endl;
  }
}

void Date::setJour(int jour) {
  if (jour < 1 || jour > 31) {
    std::cerr << "Le jour n'est pas valide";
  } else {
    d_jour = jour;
  }
}

// opérations

Date Date::operator+=(int nbJour) {
  int nv_jour = d_jour + nbJour;
  if (nv_jour > 31) {
    if (d_mois  % 2 == 0) { 
      d_jour = nv_jour - 31;
    } else {
      d_jour = nv_jour - 30;
    }
    d_mois = d_mois + 1;
    if (d_mois == 1){
        d_annee = d_annee + 1;
    }
  } else {
    d_jour = nv_jour;
  }
  return *this;
}

Date Date::operator+(int nbJour) const {
  Date nv_date = *this;
  nv_date += nbJour; // on réutilise l'opérateur +=
  return nv_date;
}

Date Date::operator++() {
  int nv_jour = d_jour + 1;
  if (nv_jour > 31) {
    d_mois = d_mois + 1;
    if (d_mois == 1) {
      d_annee = d_annee + 1;
    }
    d_jour = nv_jour - 31;
  } else {
    d_jour = nv_jour;
  }
  return *this;
}

bool Date::operator<(const Date &other) const {
  if (d_annee != other.d_annee)
    return d_annee < other.d_annee;
  if (d_mois != other.d_mois)
    return d_mois < other.d_mois;
  return d_jour < other.d_jour;
}

bool Date::operator==(const Date &other) const {
  if (d_annee == other.d_annee && d_mois == other.d_mois &&
      d_jour == other.d_jour) {
    return true;
  } else {
    return false;
  }
}

// opérateur d'affichage

std::ostream &operator<<(std::ostream &os, const Date &d) {
  os << d.getAnnee() << "/" << d.getMois() << "/" << d.getJour();
  return os;
}
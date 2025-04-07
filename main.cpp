#include "Station.h"
#include <iostream>

int main() {
  // Création d'un objet en vu des tests
  Station station1("1;Station A;48.8566;2.3522;35");
  Station station2("2;Station B;45.7640;4.8357;150");

  // Test lecture des informations
  std::cout << "ID: " << station1.getId() << ", Nom: " << station1.getName()
            << ", Latitude: " << station1.getLatitude()
            << ", Longitude: " << station1.getLongitude()
            << ", Altitude: " << station1.getAltitude() << std::endl;

  std::cout << "ID: " << station2.getId() << ", Nom: " << station2.getName()
            << ", Latitude: " << station2.getLatitude()
            << ", Longitude: " << station2.getLongitude()
            << ", Altitude: " << station2.getAltitude() << std::endl;

  // Comparaison des stations avec l'opérateur ==
  if (station1 == station2) {
    std::cout << "Les deux stations sont égales." << std::endl;
  } else {
    std::cout << "Les deux stations sont différentes." << std::endl;
  }

  // Comparaison des stations avec l'opérateur <
  if (station1 < station2) {
    std::cout << "L'identifiant de la station 1 est inférieur ou égal à celui "
                 "de la station 2."
              << std::endl;
  } else {
    std::cout << "Les deux stations sont différentes." << std::endl;
  }

  // Question 6 : L'avantage de la comparaison avec l'opérateur < est que l'on
  // peut utiliser des structures de données comme les sets ou les maps qui
  // nécessitent une relation d'ordre pour fonctionner correctement. L'avnatge
  // de la comparaison avec l'opérateur == est que l'on peut vérifier si deux
  // stations sont identiques.

  return 0;
}

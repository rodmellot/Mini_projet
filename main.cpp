#include "Date.h"
#include "RadarImage.h"
#include "Station.h"
#include "tinytiff/tinytiffreader.h"
#include <fstream>
#include <iostream>

int main() {
  // Création d'un objet en vu des tests
  Station station1("1;Station A;48.8566;2.3522;35");
  Station station2("2;Station B;45.7640;4.8357;150");

  // test pour la classe Date
  Date d1(2024, 10, 1);
  d1.setJour(2);
  std::cout << d1 << std::endl;

  Date d2(2024, 10, 2);
  if (d1 == d2) {
    std::cout << "Les deux dates sont égales" << std::endl;
  }

  d2 += 30;
  std::cout << d2 << std::endl;

  if (d1 < d2) {
    std::cout << "d1 arrive avant d2" << std::endl;
  }

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

  // test Q13

  RadarImage image(
      "/Donnees/radar/2024-11-01.tif"); // même en mettant le chemin complet, le
                                        // code n'arrive pas à ouvrir le fichier
                                        // tif
  if (!image.isValid()) {
    std::cerr << "Impossible de charger l'image" << std::endl;
  }
  image.getRainfallAtCoordinates(47.3456, -3.7856);
  std::cout << image.getRainfallAtCoordinates(47.3456, -3.7856) << std::endl;

  return 0;
}

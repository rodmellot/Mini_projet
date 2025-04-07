#include "Station.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ifstream inputFile("stations.csv"); // Ouverture du fichier CSV
  if (!inputFile) {
    std::cerr << "Erreur d'ouverture du fichier." << std::endl;
    return 1;
  }

  std::vector<Station> stations;
  std::string line;

  // Lecture ligne par ligne du fichier CSV
  while (std::getline(inputFile, line)) {
    Station station(line); // Création d'une station à partir de chaque ligne
    stations.push_back(station); // Ajout de la station à la liste
  }

  // Affichage des informations des stations
  for (const auto &station : stations) {
    std::cout << "ID: " << station.getId() << ", Nom: " << station.getName()
              << ", Latitude: " << station.getLatitude()
              << ", Longitude: " << station.getLongitude()
              << ", Altitude: " << station.getAltitude() << std::endl;
  }

  // Exemple d'utilisation de l'opérateur ==
  if (stations.size() > 1 && stations[0] == stations[1]) {
    std::cout << "Les deux premières stations sont égales." << std::endl;
  } else {
    std::cout << "Les deux premières stations sont différentes." << std::endl;
  }

  // Exemple d'utilisation de l'opérateur <
  if (stations.size() > 1 && stations[0] < stations[1]) {
    std::cout << "La première station a un ID inférieur à la seconde."
              << std::endl;
  } else {
    std::cout << "La première station a un ID supérieur ou égal à la seconde."
              << std::endl;
  }

  return 0;
}

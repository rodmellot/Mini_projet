#include "AveragePixel.h"
#include "ComparaisonAlgorithm.h"
#include "DataBank.h"
#include "Date.h"
#include "RadarImage.h"
#include "SimplePixel.h"
#include "Station.h"
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <unistd.h>
namespace fs = std::filesystem;

void testDate() {
  std::cout << "=== Test de la classe Date ===\n";
  Date d1(2024, 10, 1);
  d1.setJour(2);
  std::cout << "d1 : " << d1 << std::endl;

  Date d2(2024, 10, 2);
  if (d1 == d2)
    std::cout << "Les deux dates sont égales" << std::endl;

  d2 += 30;
  std::cout << "d2 après +=30 : " << d2 << std::endl;

  if (d1 < d2)
    std::cout << "d1 arrive avant d2" << std::endl;

  std::cout << std::endl;
}

void testStation() {
  std::cout << "=== Test de la classe Station ===\n";
  Station station1("1;Station A;48.8566;2.3522;35");
  Station station2("2;Station B;45.7640;4.8357;150");

  auto printStation = [](const Station &s) {
    std::cout << "ID: " << s.getId() << ", Nom: " << s.getName()
              << ", Latitude: " << s.getLatitude()
              << ", Longitude: " << s.getLongitude()
              << ", Altitude: " << s.getAltitude() << std::endl;
  };

  printStation(station1);
  printStation(station2);

  std::cout << (station1 == station2 ? "Stations égales"
                                     : "Stations différentes")
            << std::endl;
  std::cout << (station1 < station2 ? "Station1 < Station2"
                                    : "Station1 >= Station2")
            << std::endl;

  std::cout << "\n";
}

void testDatabank() {
  std::cout << "=== Test de la classe Databank ===\n";
  try {
    Databank db("Donnees/stations.csv", "Donnees/donnees.csv");

    std::cout << "Stations chargées :" << std::endl;
    for (const auto &station : db) {
      std::cout << " - " << station.getName() << std::endl;
    }

    Station testStation("22016001;ILE-DE-BREHAT;48.855167;-3.004500;25");
    Date testDate(2024, 11, 20);

    auto releve = db.getReleve(testStation, testDate);
    float tempMin, tempMax, tempMoy, pluie;
    std::tie(tempMin, tempMax, tempMoy, pluie) = releve;

    std::cout << "\nDonnées pour la station '" << testStation.getName()
              << "' le " << testDate << " :" << std::endl;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << " - Temp min : " << tempMin << std::endl;
    std::cout << " - Temp max : " << tempMax << std::endl;
    std::cout << " - Temp moy : " << tempMoy << std::endl;
    std::cout << " - Pluie    : "
              << (std::isnan(pluie) ? "données indisponibles"
                                    : std::to_string(pluie))
              << std::endl;

  } catch (const std::exception &e) {
    std::cerr << "Erreur : " << e.what() << std::endl;
  }

  std::cout << "\n";
}

void testRadarImage() {
  std::cout << "=== Test de la classe RadarImage ===\n";

  // Spécifier le chemin vers l'image radar
  std::string cheminFichier = "Donnees/radar/2024-11-20.tif";
  std::cout << "Tentative d’ouverture du fichier : " << cheminFichier << "\n";

  RadarImage radar(cheminFichier);

  if (!radar.isValid()) {
    std::cerr << "[ERREUR] L’image radar n’a pas pu être chargée.\n";
    return;
  }

  // Coordonnées de test
  float lat = 48.855167;
  float lon = -3.004500;
  float pluie = radar.getRainfallAtCoordinates(lat, lon);

  std::cout << "Pluviométrie au point (" << lat << ", " << lon
            << ") : " << pluie << " mm\n";
}

// Partie 2 - Question 5
void testComparaisonAlgorithm(const Date &date, const int n) {
  if (n != 1 && n != 2) {
    std::cerr << "Le numéro d'algorithme doit être 1 ou 2" << std::endl;
    return;
  }
  try {
    Databank db("Donnees/stations.csv", "Donnees/donnees.csv");

    if (n == 1) {
      std::cout << "=== Utilisation de SimplePixel ===\n";
      SimplePixel simplepixel(db);
      simplepixel.getDataForDay(date);
    }

    if (n == 2) {
      std::cout << "=== Utilisation d'AveragePixel ===\n";
      AveragePixel averagepixel(db);
      averagepixel.getDataForDay(date);
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

int main() {
  testDate();
  testStation();
  testDatabank();
  testRadarImage();
  testComparaisonAlgorithm(Date(2024, 11, 20), 1);
  testComparaisonAlgorithm(Date(2024, 11, 20), 2);

  return 0;
}
#include "DataBank.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

// Constructeur
Databank::Databank(const std::string &stationsFile,
                   const std::string &dataFile) {
  loadStations(stationsFile);
  loadData(dataFile);
}

// Méthodes pour obtenir les itérateurs
Databank::StationIterator Databank::begin() { return stations.begin(); }

Databank::StationIterator Databank::end() { return stations.end(); }

// Méthode pour récupérer la pluviométrie d'une station à une date donnée
double Databank::getPrecipitation(const Station &station,
                                  const Date &date) const {
  // Recherche de la donnée pour la station et la date
  for (const auto &d : data) {
    if (d.station == station && d.date == date) {
      return d.precipitation;
    }
  }
  // Retourner NAN si aucune donnée valide n'est trouvée
  return NAN;
}

// Méthode privée pour charger les stations depuis un fichier
void Databank::loadStations(const std::string &stationsFile) {
  std::ifstream file(stationsFile);
  if (!file.is_open()) {
    throw std::runtime_error("Impossible d'ouvrir le fichier des stations");
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream stream(line);
    Station station;
    station.loadFromStream(stream);
    stations.push_back(station);
  }

  file.close();
}

// Méthode privée pour charger les données depuis un fichier
void Databank::loadData(const std::string &dataFile) {
  std::ifstream file(dataFile);
  if (!file.is_open()) {
    throw std::runtime_error("Impossible d'ouvrir le fichier des données");
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream stream(line);
    Data dataEntry;
    dataEntry.station.loadFromStream(stream); // Lecture de la station
    dataEntry.date = Date(line);              // Lecture de la date
    stream >> dataEntry.precipitation;        // Lecture de la pluviométrie

  // Filtrage des données pour ne

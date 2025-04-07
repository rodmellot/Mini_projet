#include "DataBank.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>

// Constructeur
Databank::Databank(const std::string &stationsFile, const std::string &dataFile)
    : dataIndex() { // Initialize dataIndex here
  dataIndex = {};
  loadStations(stationsFile);
  loadData(dataFile);
}

// Méthodes pour obtenir les itérateurs
Databank::StationIterator Databank::begin() { return stations.begin(); }

Databank::StationIterator Databank::end() { return stations.end(); }

// Méthode pour récupérer les relevés d'une station à une date donnée
std::tuple<float, float, float, float>
Databank::getReleve(const Station &station, const Date &date) const {
  auto stationIt = dataIndex.find(station);
  if (stationIt != dataIndex.end()) {
    auto dateIt = stationIt->second.find(date);
    if (dateIt != stationIt->second.end()) {
      return dateIt->second; // Retourner le tuple de relevés trouvé
    }
  }
  // Retourner un tuple de NaN si aucune donnée n'est trouvée
  return std::make_tuple(NAN, NAN, NAN, NAN);
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
    Station station(line); // Constructeur qui prend une ligne CSV
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

    // Lecture de la station
    std::string stationData;
    std::getline(stream, stationData, ';');
    Station station(stationData);

    // Lecture de la date (format AAAAMMJJ)
    std::string dateStr;
    std::getline(stream, dateStr, ';');
    int annee = std::stoi(dateStr.substr(0, 4));
    int mois = std::stoi(dateStr.substr(4, 2));
    int jour = std::stoi(dateStr.substr(6, 2));
    Date date(annee, mois, jour);

    // Filtrage des données entre le 1er octobre 2024 et le 28 février 2025
    if ((annee > 2024 || (annee == 2024 && mois >= 10)) &&
        (annee < 2025 || (annee == 2025 && mois <= 2))) {

      // Lecture des autres données
      float precipitation, tempMin, tempMax, tempMoy;
      std::getline(stream, line, ';');
      precipitation = std::stof(line);

      std::getline(stream, line, ';');
      tempMin = std::stof(line);

      std::getline(stream, line, ';');
      tempMax = std::stof(line);

      std::getline(stream, line, ';');
      tempMoy = std::stof(line);

      // Création de l'entrée Data et ajout dans l'index
      Data dataEntry{station, date, precipitation,
                     std::make_tuple(tempMin, tempMax, tempMoy, precipitation)};
      dataIndex[station][date] = std::move(dataEntry.releve);
    }
  }

  file.close();
}

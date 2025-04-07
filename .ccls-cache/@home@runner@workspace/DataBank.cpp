#include "DataBank.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>

// Constructeur
Databank::Databank(const std::string &stationsFile,
                   const std::string &dataFile) {
  loadStations(stationsFile);
  loadData(dataFile);
}

Databank::StationIterator Databank::begin() { return stations.begin(); }

Databank::StationIterator Databank::end() { return stations.end(); }

std::tuple<float, float, float, float>
Databank::getReleve(const Station &station, const Date &date) const {
  // Utilisation de map à la place de unordered_map
  auto stationIt = dataIndex.find(station);
  if (stationIt != dataIndex.end()) {
    auto dateIt = stationIt->second.find(date);
    if (dateIt != stationIt->second.end()) {
      return dateIt->second;
    }
  }
  // Retourner un tuple de NaN si aucune donnée n'est trouvée
  return std::make_tuple(NAN, NAN, NAN, NAN);
}

void Databank::loadStations(const std::string &stationsFile) {
  std::ifstream file(stationsFile);
  if (!file.is_open()) {
    throw std::runtime_error("Impossible d'ouvrir le fichier des stations");
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream stream(line);
    Station station(line);
    stations.push_back(station);
  }

  file.close();
}

void Databank::loadData(const std::string &dataFile) {
  std::ifstream file(dataFile);
  if (!file.is_open()) {
    throw std::runtime_error("Impossible d'ouvrir le fichier des données");
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream stream(line);

    std::string stationData;
    std::getline(stream, stationData, ';');
    Station station(stationData);

    std::string dateStr;
    std::getline(stream, dateStr, ';');
    int annee = std::stoi(dateStr.substr(0, 4));
    int mois = std::stoi(dateStr.substr(4, 2));
    int jour = std::stoi(dateStr.substr(6, 2));
    Date date(annee, mois, jour);

    // Filtrage des données entre le 1er octobre 2024 et le 28 février 2025
    if ((annee > 2024 || (annee == 2024 && mois >= 10)) &&
        (annee < 2025 || (annee == 2025 && mois <= 2))) {

      float tempMin, tempMax, tempMoy;
      std::getline(stream, line, ';'); // Ignorer la pluie (précipitation)
      std::getline(stream, line, ';');
      tempMin = std::stof(line);

      std::getline(stream, line, ';');
      tempMax = std::stof(line);

      std::getline(stream, line, ';');
      tempMoy = std::stof(line);

      // Création de l'entrée Data et ajout dans l'index
      Data dataEntry{station, date,
                     std::make_tuple(tempMin, tempMax, tempMoy,
                                     NAN)}; // Remplacer la pluie par NaN
      dataIndex[station][date] = std::move(dataEntry.releve);
    }
  }

  file.close();
}

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
  auto stationIt = dataIndex.find(station);
  if (stationIt != dataIndex.end()) {
    auto dateIt = stationIt->second.find(date);
    if (dateIt != stationIt->second.end()) {
      return dateIt->second;
    }
  }
  return std::make_tuple(NAN, NAN, NAN, NAN);
}

void Databank::loadStations(const std::string &stationsFile) {
  std::ifstream file(stationsFile);
  if (!file.is_open()) {
    throw std::runtime_error("Impossible d'ouvrir le fichier des stations");
  }

  std::string line;
  std::getline(file, line);

  while (std::getline(file, line)) {
    if (line.empty())
      continue;
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
  std::getline(file, line); // Ignorer l'en-tête

  while (std::getline(file, line)) {
    std::stringstream stream(line);
    std::string field;

    // Lecture ID de station
    std::getline(stream, field, ';');
    std::string id = field;

    // Ignorer NOM_USUEL, LAT, LON, ALTI
    for (int i = 0; i < 4; ++i) {
      std::getline(stream, field, ';');
    }

    // Construction minimale de la Station à partir du seul ID
    Station station(id + ";Placeholder;0;0;0");

    // Lecture date
    std::getline(stream, field, ';');
    int annee = std::stoi(field.substr(0, 4));
    int mois = std::stoi(field.substr(4, 2));
    int jour = std::stoi(field.substr(6, 2));
    Date date(annee, mois, jour);

    // Vérification période
    if ((annee > 2024 || (annee == 2024 && mois >= 10)) &&
        (annee < 2025 || (annee == 2025 && mois <= 2))) {

      // Lecture RR, TN, TX, TM
      float pluie, tempMin, tempMax, tempMoy;

      std::getline(stream, field, ';');
      pluie = field.empty() ? NAN : std::stof(field);

      std::getline(stream, field, ';');
      tempMin = field.empty() ? NAN : std::stof(field);

      std::getline(stream, field, ';');
      tempMax = field.empty() ? NAN : std::stof(field);

      std::getline(stream, field, ';');
      tempMoy = field.empty() ? NAN : std::stof(field);

      dataIndex[station][date] =
          std::make_tuple(tempMin, tempMax, tempMoy, pluie);
    }
  }

  file.close();
}

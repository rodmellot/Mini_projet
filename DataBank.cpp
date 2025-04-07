#include "DataBank.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

// Constructeur
Databank::Databank(const std::string &stationsFile,
                   const std::string &dataFile) {
  loadStations(stationsFile);
  loadData(dataFile);
}

// Méthodes pour obtenir les itérateurs
Databank::StationIterator Databank::begin() { return stations.begin(); }

Databank::StationIterator Databank::end() { return stations.end(); }

// Méthode pour récupérer les relevés d'une station à une date donnée
std::tuple<float, float, float, float>
Databank::getReleve(const Station &station, const Date &date) const {
  // Recherche rapide via l'indexation des données par station et date
  auto stationIt = dataIndex.find(station);
  if (stationIt != dataIndex.end()) {
    auto dateIt = stationIt->second.find(date);
    if (dateIt != stationIt->second.end()) {
      return dateIt->second; // Retourne le tuple de relevés trouvé
    }
  }
  // Retourner un tuple de NaN si aucune donnée valide n'est trouvée
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
    std::string stationData;
    std::getline(stream, stationData, ';');
    Station station(stationData);

    std::string dateStr;
    std::getline(stream, dateStr, ';');
    int annee = std::stoi(dateStr.substr(0, 4));
    int mois = std::stoi(dateStr.substr(4, 2));
    int jour = std::stoi(dateStr.substr(6, 2));
    Date date(annee, mois, jour);
    
    Data dataEntry{station, date};

    // Lecture de la station et séparation par ;
    std::string stationData;
    std::getline(stream, stationData, ';'); // Station est la première colonne
    Station station(stationData);

    // Lecture de la date (format AAAAMMJJ)
    int annee, mois, jour;
    std::string dateStr;
    std::getline(stream, dateStr,
                 ';'); // Récupération de la date en format string
    annee = std::stoi(dateStr.substr(0, 4)); // Extraction de l'année
    mois = std::stoi(dateStr.substr(4, 2));  // Extraction du mois
    jour = std::stoi(dateStr.substr(6, 2));  // Extraction du jour

    Date date(annee, mois, jour);

    // Filtrage du 1er octobre 2024 au 28 février 2025
    if ((annee > 2024 || (annee == 2024 && mois >= 10)) &&
        (annee < 2025 || (annee == 2025 && mois <= 2))) {

      // Lecture des autres données : précipitation, température min, temp max,
      // temp moy
      float precipitation, tempMin, tempMax, tempMoy;
      std::getline(stream, line, ';'); // Lecture de la précipitation
      precipitation = std::stof(line);

      std::getline(stream, line, ';'); // Lecture de la température minimale
      tempMin = std::stof(line);

      std::getline(stream, line, ';'); // Lecture de la température maximale
      tempMax = std::stof(line);

      std::getline(stream, line, ';'); // Lecture de la température moyenne
      tempMoy = std::stof(line);

      // Construction du relevé de données
      dataEntry.station = station;
      dataEntry.date = date;
      dataEntry.precipitation = precipitation;
      dataEntry.releve =
          std::make_tuple(tempMin, tempMax, tempMoy, precipitation);

      // Ajout des données à l'index
      dataIndex[dataEntry.station][dataEntry.date] = dataEntry.releve;
    }
  }

  file.close();
}

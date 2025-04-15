#include "SimplePixel.h"
#include <iostream>

SimplePixel::SimplePixel(Databank &db) : databank(db) {}

void SimplePixel::getDataForDay(const Date &date) {
  // Parcours de toutes les stations et affichage des données pour chaque
  // station
  for (auto it = databank.begin(); it != databank.end(); ++it) {
    const Station &station = *it;
    auto releve = databank.getReleve(station, date);

    // Extraction des valeurs du tuple
    float tempMin, tempMax, tempMoy, precipitation;
    std::tie(tempMin, tempMax, tempMoy, precipitation) = releve;

    // Affichage des informations
    std::cout << "Station ID: " << station.getId() << ", "
              << "Station Name: " << station.getName() << ", "
              << "Pluviométrie Station: " << precipitation << " mm, "
              << "Pluviométrie Radar: " << precipitation
              << " mm\n"; // Utiliser la même pluviométrie ici
  }
}

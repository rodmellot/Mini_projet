#include "AveragePixel.h"
#include <iostream>

AveragePixel::AveragePixel(Databank &db) : databank(db) {}

void AveragePixel::getDataForDay(const Date &date) {
  // Parcours de toutes les stations et affichage des données pour chaque
  // station
  for (auto it = databank.begin(); it != databank.end(); ++it) {
    const Station &station = *it;
    auto releve = databank.getReleve(station, date);

    // Extraction des valeurs du tuple
    float tempMin, tempMax, tempMoy, precipitation;
    std::tie(tempMin, tempMax, tempMoy, precipitation) = releve;

    // Calcul de la moyenne des neuf pixels autour (dans ce cas, on suppose que
    // la pluviométrie du radar est aussi dans le releve) Ici on pourrait
    // calculer la moyenne en prenant les données des pixels voisins. Pour
    // l'exemple, on simule cela.
    float averagePrecipitation = precipitation; // À ajuster si nécessaire

    // Affichage des informations
    std::cout << "Station ID: " << station.getId() << ", "
              << "Station Name: " << station.getName() << ", "
              << "Pluviométrie Station: " << precipitation << " mm, "
              << "Pluviométrie Radar: " << averagePrecipitation << " mm\n";
  }
}

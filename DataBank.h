#ifndef DATABANK_H
#define DATABANK_H

#include <vector>
#include <string>
#include <iterator>
#include <cmath>  // Pour NAN
#include "Station.h"
#include "Date.h"

class Databank {
public:
    // Alias pour l'itérateur du conteneur de stations
    using StationIterator = std::vector<Station>::iterator;

    // Structure pour stocker une donnée associée à une station et une date
    struct Data {
        Station station;
        Date date;
        double precipitation;

        // Méthode pour vérifier si la donnée est valide
        bool isValid() const {
            return precipitation >= 0;
        }
    };

    // Constructeur qui charge les fichiers
    Databank(const std::string& stationsFile, const std::string& dataFile);

    // Méthodes pour obtenir les itérateurs
    StationIterator begin();
    StationIterator end();

    // Méthode pour récupérer la pluviométrie d'une station à une date donnée
    double getPrecipitation(const Station& station, const Date& date) const;

private:
    // Méthodes privées pour lire les fichiers
    void loadStations(const std::string& stationsFile);
    void loadData(const std::string& dataFile);

    // Conteneurs pour stocker les stations et les données
    std::vector<Station> stations;
    std::vector<Data> data;
};

#endif // DATABANK_H

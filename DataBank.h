#ifndef DATABANK_H
#define DATABANK_H

#include <unordered_map>
#include <vector>
#include <string>
#include <tuple>
#include "Station.h"
#include "Date.h"

class Databank {
public:
    using StationIterator = std::vector<Station>::iterator;

    // Structure pour stocker les données
    struct Data {
        Station station;
        Date date;
        float precipitation;
        std::tuple<float, float, float, float> releve;  // Température Minimale, Température Maximale, Température Moyenne, Pluviométrie
    };

    Databank(const std::string& stationsFile, const std::string& dataFile);

    // Accès aux itérateurs pour les stations
    StationIterator begin();
    StationIterator end();

    // Récupérer les relevés (températures et précipitations) pour une station à une date
    std::tuple<float, float, float, float> getReleve(const Station& station, const Date& date) const;

private:
    // Méthodes privées pour charger les données
    void loadStations(const std::string& stationsFile);
    void loadData(const std::string& dataFile);

    std::vector<Station> stations;
    std::unordered_map<Station, std::unordered_map<Date, std::tuple<float, float, float, float>>> dataIndex;
};

#endif /* DATABANK_H */

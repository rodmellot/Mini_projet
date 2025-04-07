#ifndef DATABANK_H
#define DATABANK_H

#include <map>
#include <vector>
#include <string>
#include <tuple>
#include "Station.h"
#include "Date.h"

// La structure de recherche sera définie comme suit : Une map ordonnée dont la clé est la Station et la valeur est une autre map ordonnée, dont la clé est la Date et la valeur est le tuple Relevé <float, float, float, float> (Température Minimale, Température Maximale, Température Moyenne, Pluviométrie). (Q7)

class Databank {
public:
    // Alias pour les itérateurs sur les stations (Q8)
    using StationIterator = std::vector<Station>::iterator;

    // Structure pour stocker les données
    struct Data {
        Station station;
        Date date;
        std::tuple<float, float, float, float> releve;  // Température Minimale, Température Maximale, Température Moyenne, Pluviométrie
    };

    // Constructeur (Q11)
    Databank(const std::string& stationsFile, const std::string& dataFile);

    // Remplace les accesseurs pour les stations (Q9)
    StationIterator begin();
    StationIterator end();

    // Récupérer les relevés (températures et précipitations) pour une station à une date (Q12)
    std::tuple<float, float, float, float> getReleve(const Station& station, const Date& date) const;

private:
    // Q10
    void loadStations(const std::string& stationsFile);
    void loadData(const std::string& dataFile);

    std::vector<Station> stations;
    std::map<Station, std::map<Date, std::tuple<float, float, float, float>>> dataIndex;
};

#endif /* DATABANK_H */

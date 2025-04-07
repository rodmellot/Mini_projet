#ifndef DATABANK_H
#define DATABANK_H

#include <unordered_map>
#include <vector>
#include <string>
#include <tuple>
#include "Station.h"
#include "Date.h"


// La structure de recherche sera définie comme suit : Une unordered_map dont la clé est la Station et la valeur est une autre unordered_map, dont la clé est la Date et la valeur est le tuple Relevé <float, float, float, float> (Pluviométrie, Température Minimale, Température Maximale, Température Moyenne).(Q7)

class Databank {
public:
    // Alias pour les itérateurs sur les stations (Q8)
    using StationIterator = std::vector<Station>::iterator;

    // Structure pour stocker les données
    struct Data {
        Station station;
        Date date;
        float precipitation;
        std::tuple<float, float, float, float> releve;  // Température Minimale, Température Maximale, Température Moyenne, Pluviométrie
    };
    // Constructeur (Q11)
    Databank(const std::string& stationsFile, const std::string& dataFile) ;

    // Remplace les accesseurs pour les stations (Q9)
    StationIterator begin();
    StationIterator end();

    // Récupérer les relevés (températures et précipitations) pour une station à une date (Q12)
    std::tuple<float, float, float, float> getReleve(const Station& station, const Date& date) const;

private:
    // Méthodes privées pour charger les données (Q10)
    void loadStations(const std::string& stationsFile);
    void loadData(const std::string& dataFile);

    std::vector<Station> stations;
    std::unordered_map<Station, std::unordered_map<Date, std::tuple<float, float, float, float>>> dataIndex;
};

#endif /* DATABANK_H */

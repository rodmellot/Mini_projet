#ifndef DATABANK_H
#define DATABANK_H

#include <unordered_map>
#include <vector>
#include <string>
#include <tuple>
#include "Station.h"
#include "Date.h"

// La structure de recherche sera définie comme suit : Une unordered_map dont la clé est la Station et la valeur est une autre unordered_map,
// dont la clé est la Date et la valeur est le tuple Relevé <float, float, float, float> (Pluviométrie, Température Minimale, Température Maximale, Température Moyenne).

class Databank {
public:
    // Alias de type vers le type iterator du conteneur de stations
    using StationIterator = std::vector<Station>::iterator;

    // Structure de la forme Station, Date, Relevé (Pluviométrie, Température Minimale, Température Maximale, Température Moyenne)
    struct Data {
        Station station;
        Date date;
        float precipitation;               // Pluviométrie
        std::tuple<float, float, float, float> releve;  // Température Minimale, Température Maximale, Température Moyenne
    };

    // Constructeur qui charge les fichiers
    Databank(const std::string& stationsFile, const std::string& dataFile);

    // Pour remplacer les accesseurs, permet d'itérer sur les stations
    StationIterator begin();
    StationIterator end();

    // Méthode pour récupérer les relevés (précipitation, températures) d'une station à une date donnée
    std::tuple<float, float, float, float> getReleve(const Station& station, const Date& date) const;

private:
    // Méthodes privées pour lire les fichiers
    void loadStations(const std::string& stationsFile);
    void loadData(const std::string& dataFile);

    // Conteneur pour stocker les stations
    std::vector<Station> stations;

    // Utilisation d'une unordered_map pour indexer les données par station et date
    std::unordered_map<Station, std::unordered_map<Date, std::tuple<float, float, float, float>>> dataIndex;
};

#endif /* DATABANK_H */

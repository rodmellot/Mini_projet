#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <string>

class Station
{
private:
    int id;
    std::string name;
    float latitude;
    float longitude;
    int altitude;

public:
    Station(const std::string& csvLine);

    int getId() const { return id; }
    std::string getName() const { return name; }
    float getLatitude() const { return latitude; }
    float getLongitude() const { return longitude; }
    int getAltitude() const { return altitude; }
};

bool operator==(const Station& other) const;
bool operator<(const Station& other) const;

#endif /* STATION_H */

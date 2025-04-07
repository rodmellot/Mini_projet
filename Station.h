
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

    int getId() const;
    std::string getName() const;
    float getLatitude() const;
    float getLongitude() const;
    int getAltitude() const;

};

bool operator==(const Station& other) const;
bool operator<(const Station& other) const;

#endif /* STATION_H */

#include "Station.h"
#include <sstream>

Station::Station(const std::string &csvLine) {
  std::stringstream ss(csvLine);
  std::string field;

  std::getline(ss, field, ';');
  id = std::stoi(field);

  std::getline(ss, name, ';');

  std::getline(ss, field, ';');
  latitude = std::stof(field);

  std::getline(ss, field, ';');
  longitude = std::stof(field);

  std::getline(ss, field, ';');
  altitude = std::stoi(field);
}

int Station::getId() const { return id; }

std::string Station::getName() const { return name; }

float Station::getLatitude() const { return latitude; }

float Station::getLongitude() const { return longitude; }

int Station::getAltitude() const { return altitude; }

bool Station::operator==(const Station &other) const { return id == other.id; }

bool Station::operator<(const Station &other) const { return id < other.id; }

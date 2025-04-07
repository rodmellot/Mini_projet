#ifndef RADAR_IMAGE_H
#define RADAR_IMAGE_H

#include <string>
#include <vector>

#include "tinytiff/tinytiffreader.h"


class RadarImage
{
private:
	std::string m_filename;
	static constexpr float MIN_LATITUDE = 46.8382730;
	static constexpr float MAX_LATITUDE = 49.9235863;
	static constexpr float MIN_LONGITUDE = -6.3528495;
	static constexpr float MAX_LONGITUDE = -0.8496449;
	static constexpr float CONVERSION_FACTOR = 0.01; //à multiplier pour la pluviométrie
	int m_width = 0;
	int m_height = 0;
	bool m_valid = false;
	std::vector<uint16_t> m_data;

public:
	explicit RadarImage(const std::string& filename);
	float getMinLatitude() const;
	float getMaxLatitude() const;
	float getMinLongitude() const;
	float getMaxLongitude() const;
	int getWidth() const;
	int getHeight() const;
	bool isValid() const;
	uint16_t getDataAtPixel(int row, int column) const;
//Q13
  float getRainfallAtCoordinates(float lat, float lon) const;
};

#endif

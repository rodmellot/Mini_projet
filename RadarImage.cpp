#include <iostream>
#include <memory>

#include "RadarImage.h"

RadarImage::RadarImage(const std::string& filename) :
	m_filename{filename}
{
	std::unique_ptr<TinyTIFFReaderFile, typeof(&TinyTIFFReader_close)> file{
		TinyTIFFReader_open(filename.c_str()), &TinyTIFFReader_close
	};

	if (!file) {
		std::cerr << "Impossible d'ouvrir le fichier " << filename << "\n";
		return;
	}

	const uint32_t frames = TinyTIFFReader_countFrames(file.get());
	const uint32_t width = TinyTIFFReader_getWidth(file.get());
	const uint32_t height = TinyTIFFReader_getHeight(file.get());
	const uint16_t samples = TinyTIFFReader_getSamplesPerPixel(file.get());
	const uint16_t bitspersample = TinyTIFFReader_getBitsPerSample(file.get(), 0);

	if (TinyTIFFReader_wasError(file.get()) ||
	    frames != 1 ||
	    width <= 0 ||
	    height <= 0 ||
	    samples != 1 ||
	    bitspersample != 16) {
		std::cerr << "Le format du fichier n'est pas celui attendu\n";
		return;
	}

	m_width = width;
	m_height = height;

	m_data.resize(width*height);
	TinyTIFFReader_getSampleData_s(file.get(), m_data.data(), m_data.size() * 2, 0);


	if (TinyTIFFReader_wasError(file.get())) {
		std::cerr << "Impossible d'extraire les données du fichier\n";
		return;
	}

	m_valid = true;
}

float RadarImage::getMinLatitude() const
{
	return MIN_LATITUDE;
}

float RadarImage::getMaxLatitude() const
{
	return MAX_LATITUDE;
}

float RadarImage::getMinLongitude() const
{
	return MIN_LONGITUDE;
}

float RadarImage::getMaxLongitude() const
{
	return MAX_LONGITUDE;
}

int RadarImage::getWidth() const
{
	return m_width;
}

int RadarImage::getHeight() const
{
	return m_height;
}

bool RadarImage::isValid() const
{
	return m_valid;
}

uint16_t RadarImage::getDataAtPixel(int row, int column) const
{
	if (row < 0 || row >= m_height || column < 0 || column >= m_width) {
		std::cerr << "Pixel hors-limite " << row << "x" << column << "\n";
		return 0;
	}

	return m_data[row * m_height + column];
}

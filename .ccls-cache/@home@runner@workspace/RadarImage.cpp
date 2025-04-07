#include <iostream>
#include <memory>
#include <cmath> //pour std::round

#include "RadarImage.h"
#include "tinytiff/tinytiffreader.h"

RadarImage::RadarImage(const std::string &filename) : m_filename{filename} {
  std::unique_ptr<TinyTIFFReaderFile, decltype(&TinyTIFFReader_close)> file{
      TinyTIFFReader_open(filename.c_str()), &TinyTIFFReader_close};

  if (!file) {
    std::cerr << "Impossible d'ouvrir le fichier " << filename << "\n";
    return;
  }

  const uint32_t frames = TinyTIFFReader_countFrames(file.get());
  const uint32_t width = TinyTIFFReader_getWidth(file.get());
  const uint32_t height = TinyTIFFReader_getHeight(file.get());
  const uint16_t samples = TinyTIFFReader_getSamplesPerPixel(file.get());
  const uint16_t bitspersample = TinyTIFFReader_getBitsPerSample(file.get(), 0);

  if (TinyTIFFReader_wasError(file.get()) || frames != 1 || width <= 0 ||
      height <= 0 || samples != 1 || bitspersample != 16) {
    std::cerr << "Le format du fichier n'est pas celui attendu\n";
    return;
  }

  m_width = width;
  m_height = height;

  m_data.resize(width * height);
  TinyTIFFReader_getSampleData_s(file.get(), m_data.data(), m_data.size() * 2,
                                 0);

  if (TinyTIFFReader_wasError(file.get())) {
    std::cerr << "Impossible d'extraire les données du fichier\n";
    return;
  }

  m_valid = true;
}

float RadarImage::getMinLatitude() const { return MIN_LATITUDE; }

float RadarImage::getMaxLatitude() const { return MAX_LATITUDE; }

float RadarImage::getMinLongitude() const { return MIN_LONGITUDE; }

float RadarImage::getMaxLongitude() const { return MAX_LONGITUDE; }

int RadarImage::getWidth() const { return m_width; }

int RadarImage::getHeight() const { return m_height; }

bool RadarImage::isValid() const { return m_valid; }

uint16_t RadarImage::getDataAtPixel(int row, int column) const {
  if (row < 0 || row >= m_height || column < 0 || column >= m_width) {
    std::cerr << "Pixel hors-limite " << row << "x" << column << "\n";
    return 0;
  }

  return m_data[row * m_height + column];
}

//Q13

float RadarImage::getRainfallAtCoordinates(float lat, float lon) const{
  if (lat < MIN_LATITUDE || lat > MAX_LATITUDE || lon < MIN_LONGITUDE || lon > MAX_LONGITUDE){
    std::cerr << "Les coordonnées sont hors-limite" << std::endl;
    return 0;
  }
  //on doit convertir les coordonnées en pixels
  //première étape: calculer le ratio des coordonnées pour savoir où on se situe sur l'image
  float lat_position = (MAX_LATITUDE - lat) / (MAX_LATITUDE - MIN_LATITUDE); 
  float lon_position = (lon - MIN_LONGITUDE) / (MAX_LONGITUDE - MIN_LONGITUDE); 
  //deuxième étape: calculer les pixels correspondants
  int pixel_ligne = static_cast<int>(std::round(lat_position * m_height)); //on arrondit au pixel le plus proche, et on le convertit en int
  int pixel_colonne = static_cast<int>(std::round(lon_position * m_width));
  //troisième étape : on fait attention aux bornes
  if (pixel_ligne >= m_height){pixel_ligne = m_height - 1;} 
  if (pixel_colonne >= m_width){pixel_colonne = m_width - 1;}
  //quatrième étape: on retourne la valeur de la pluie à ce pixel
  return getDataAtPixel(pixel_ligne, pixel_colonne)*CONVERSION_FACTOR;
}

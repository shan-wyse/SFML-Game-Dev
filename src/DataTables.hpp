# ifndef DATA_TABLES_HPP
# define DATA_TABLES_HPP

#include <vector>
#include "ResourceIdentifiers.hpp"

struct AircraftData
{
  int                       hitpoints;
  float                     speed;
  Textures::Id              texture;
  std::vector<Direction>    directions;
};

std::vector<AircraftData> initializeAircraftData();

#endif // DATA_TABLES_HPP

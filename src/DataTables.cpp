#include "DataTables.hpp"
#include "Aircraft.hpp"

std::vector<AircraftData> initializeAircraftData()
{
  std::vector<AircraftData> data(Aircraft::Count);

  data[Aircraft::Eagle].hitpoints = 100;
  data[Aircraft::Eagle].speed = 200.f;
  data[Aircraft::Eagle].texture = Textures::Id::Eagle;

  data[Aircraft::Raptor].hitpoints = 20;
  data[Aircraft::Raptor].speed = 80.f;
  data[Aircraft::Raptor].texture = Textures::Id::Raptor;
  data[Aircraft::Raptor].directions.push_back(Direction(45, 80));
  data[Aircraft::Raptor].directions.push_back(Direction(-45, 160));
  data[Aircraft::Raptor].directions.push_back(Direction(45, 80));

  data[Aircraft::Avenger].hitpoints = 10;
  data[Aircraft::Avenger].speed = 60.f;
  data[Aircraft::Avenger].textures = Textures::Id::Avenger;
  data[Aircraft::Avenger].directions.push_back(Direction(45, 50));
  data[Aircraft::Avenger].directions.push_back(Direction(0, 50));
  data[Aircraft::Avenger].directions.push_back(Direction(-45, 100));
  data[Aircraft::Avenger].directions.push_back(Direction(0, 50));
  data[Aircraft::Avenger].directions.push_back(Direction(45, 50));

  return data;
}

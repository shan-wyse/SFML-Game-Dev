# ifndef DATA_TABLES_HPP
# define DATA_TABLES_HPP

#include <vector>
#include <functional>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include "ResourceIdentifiers.hpp"

class Aircraft;

struct Direction
{
                                        Direction(float distance, float angle);
  float                                 distance;
  float                                 angle;
};

struct AircraftData
{
  int                                   hitpoints;
  float                                 speed;
  Textures::Id                          texture;
  std::vector<Direction>                directions;
  sf::Time                              fireInterval;
};

struct ProjectileData
{
  int                                   damage;
  float                                 speed;
  Textures::Id                          texture;
};

struct PickupData
{
  std::function< void(Aircraft&) >      action;
  Textures::Id                          texture;
};

std::vector<AircraftData>               initializeAircraftData();
std::vector<ProjectileData>             initializeProjectileData();
std::vector<PickupData>                 initializePickupDate();

#endif // DATA_TABLES_HPP

# ifndef DATA_TABLES_HPP
# define DATA_TABLES_HPP

#include <vector>
#include <functional>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Rect.hpp>
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
  sf::IntRect                           textureRect;
  std::vector<Direction>                directions;
  sf::Time                              fireInterval;
  bool                                  hasRollAnimation;
};

struct ProjectileData
{
  int                                   damage;
  float                                 speed;
  Textures::Id                          texture;
  sf::IntRect                           textureRect;
};

struct PickupData
{
  std::function< void(Aircraft&) >      action;
  Textures::Id                          texture;
  sf::IntRect                           textureRect;
};

struct ParticleData
{
  sf::Color                             color;
  sf::Time                              lifetime;
};

std::vector<AircraftData>               initializeAircraftData();
std::vector<ProjectileData>             initializeProjectileData();
std::vector<PickupData>                 initializePickupData();
std::vector<ParticleData>               initializeParticleData();

#endif // DATA_TABLES_HPP

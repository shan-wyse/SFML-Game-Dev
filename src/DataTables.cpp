#include "DataTables.hpp"
#include "Aircraft.hpp"
#include "Projectile.hpp"
#include "Pickup.hpp"
#include "Particle.hpp"

using namespace std::placeholders;

Direction::Direction(float angle, float distance)
: angle(angle)
, distance(distance)
{
  // empty
}

std::vector<AircraftData> initializeAircraftData()
{
  std::vector<AircraftData> data(Aircraft::Count);

  data[Aircraft::Eagle].hitpoints = 100;
  data[Aircraft::Eagle].speed = 200.f;
  data[Aircraft::Eagle].texture = Textures::Id::Entities;
  data[Aircraft::Eagle].textureRect = sf::IntRect(0, 0, 48, 64);
  data[Aircraft::Eagle].fireInterval = sf::seconds(1);

  data[Aircraft::Raptor].hitpoints = 20;
  data[Aircraft::Raptor].speed = 80.f;
  data[Aircraft::Raptor].texture = Textures::Id::Entities;
  data[Aircraft::Raptor].textureRect = sf::IntRect(144, 0, 84, 64);
  data[Aircraft::Raptor].directions.push_back(Direction(45, 80));
  data[Aircraft::Raptor].directions.push_back(Direction(-45, 160));
  data[Aircraft::Raptor].directions.push_back(Direction(45, 80));
  data[Aircraft::Raptor].fireInterval = sf::Time::Zero;

  data[Aircraft::Avenger].hitpoints = 10;
  data[Aircraft::Avenger].speed = 60.f;
  data[Aircraft::Avenger].texture = Textures::Id::Entities;
  data[Aircraft::Avenger].textureRect = sf::IntRect(228, 0, 60, 59);
  data[Aircraft::Avenger].directions.push_back(Direction(45, 50));
  data[Aircraft::Avenger].directions.push_back(Direction(0, 50));
  data[Aircraft::Avenger].directions.push_back(Direction(-45, 100));
  data[Aircraft::Avenger].directions.push_back(Direction(0, 50));
  data[Aircraft::Avenger].directions.push_back(Direction(45, 50));
  data[Aircraft::Avenger].fireInterval = sf::seconds(2);

  return data;
}

std::vector<ProjectileData> initializeProjectileData()
{
  std::vector<ProjectileData> data(Projectile::Count);

  data[Projectile::AlliedBullet].damage = 10;
  data[Projectile::AlliedBullet].speed = 600.f;
  data[Projectile::AlliedBullet].texture = Textures::Id::Entities;
  data[Projectile::AlliedBullet].textureRect = sf::IntRect(175, 64, 3, 14);

  data[Projectile::EnemyBullet].damage = 10;
  data[Projectile::EnemyBullet].speed = 600.f;
  data[Projectile::EnemyBullet].texture = Textures::Id::Entities;
  data[Projectile::EnemyBullet].textureRect = sf::IntRect(178, 64, 3, 14);

  data[Projectile::Missile].damage = 200;
  data[Projectile::Missile].speed = 450.f;
  data[Projectile::Missile].texture = Textures::Id::Entities;
  data[Projectile::Missile].textureRect = sf::IntRect(160, 64, 15, 32);

  return data;
}

std::vector<PickupData> initializePickupData()
{
  std::vector<PickupData> data(Pickup::Count);

  data[Pickup::HealthRefill].texture = Textures::Id::Entities;
  data[Pickup::HealthRefill].textureRect = sf::IntRect(0, 64, 40, 40);
  data[Pickup::HealthRefill].action = [] (Aircraft& aircraft) { aircraft.repair(25); };

  data[Pickup::MissileRefill].texture = Textures::Id::Entities;
  data[Pickup::MissileRefill].textureRect = sf::IntRect(40, 64, 40, 40);
  data[Pickup::MissileRefill].action = std::bind(&Aircraft::collectMissiles, _1, 3);

  data[Pickup::FireSpread].texture = Textures::Id::Entities;
  data[Pickup::FireSpread].textureRect = sf::IntRect(80, 64, 40, 40);
  data[Pickup::FireSpread].action = std::bind(&Aircraft::increaseSpread, _1);

  data[Pickup::FireRate].texture = Textures::Id::Entities;
  data[Pickup::FireRate].textureRect = sf::IntRect(120, 64, 40, 40);
  data[Pickup::FireRate].action = std::bind(&Aircraft::increaseFireRate, _1);

  return data;
}

std::vector<ParticleData> initializeParticleData()
{
  std::vector<ParticleData> data(Particle::Count);

  // data[Particle::Propellant].color = sf::Color::Blue;

  return data;
}

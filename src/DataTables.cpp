#include "DataTables.hpp"
#include "Aircraft.hpp"
#include "Projectile.hpp"
#include "Pickup.hpp"

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
  data[Aircraft::Eagle].texture = Textures::Id::Eagle;
  data[Aircraft::Eagle].fireInterval = sf::seconds(1);

  data[Aircraft::Raptor].hitpoints = 20;
  data[Aircraft::Raptor].speed = 80.f;
  data[Aircraft::Raptor].texture = Textures::Id::Raptor;
  data[Aircraft::Raptor].directions.push_back(Direction(45, 80));
  data[Aircraft::Raptor].directions.push_back(Direction(-45, 160));
  data[Aircraft::Raptor].directions.push_back(Direction(45, 80));
  data[Aircraft::Eagle].fireInterval = sf::Time::Zero;

  data[Aircraft::Avenger].hitpoints = 10;
  data[Aircraft::Avenger].speed = 60.f;
  data[Aircraft::Avenger].textures = Textures::Id::Avenger;
  data[Aircraft::Avenger].directions.push_back(Direction(45, 50));
  data[Aircraft::Avenger].directions.push_back(Direction(0, 50));
  data[Aircraft::Avenger].directions.push_back(Direction(-45, 100));
  data[Aircraft::Avenger].directions.push_back(Direction(0, 50));
  data[Aircraft::Avenger].directions.push_back(Direction(45, 50));
  data[Aircraft::Eagle].fireInterval = sf::seconds(2);

  return data;
}

std::vector<ProjectileData> initializeProjectileData()
{
  std::vector<ProjectileData> data(Projectile::Cound);

  data[Projectile::AlliedBullet].damage = 10;
  data[Projectile::AlliedBullet].speed = 300.f;
  data[Projectile::AlliedBullet].texture = Textures::Bullet;

  data[Projectile::EnemyBullet].damage = 10;
  data[Projectile::EnemyBullet].speed = 300.f;
  data[Projectile::EnemyBullet].texture = Textures::Bullet;

  data[Projectile::Missile].damage = 200;
  data[Projectile::Missile].speed = 150.f;
  data[Projectile::Missile].texture = Textures::Missile;

  return data;
}

std::vector<PickupData> initializePickupData()
{
  std::vector<PickupData> data(Pickup::Count);

  data[Pickup::HealthRefill].texture = Textures::HealthRefill;
  data[Pickup::HealthRefill].action = [] (Aircraft& aircraft) { aircraft.repair(25)l };

  data[Pickup::MissileRefill].texture = Textures::MissileRefill;
  data[Pickup::MissileRefill].action = std::bind(&Aircraft::collectMissiles, _1, 3);

  data[Pickup::FireSpread].texture = Textures::FireSpread;
  data[Pickup::FireSpread].action = std::bind(&Aircraft::increaseSpread, _1);

  data[Pickup::FireRate].texture = Textures::FireRate;
  data[Pickup::FireRate].action = std::bind(&Aircraft::increaseFireRate, _1);

  return data;
}

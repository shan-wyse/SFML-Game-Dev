#include "Pickup.hpp"

Pickup::Pickup(Type type, const TextureManager& textures)
: Entity(1)
, mType(type)
, mSprite(textures.getResource(Table[type].texture))
{
  mSprite.setCenter(mSprite.getLocalBounds() / 2.f, mSprite.getLocalBounds() / 2.f);
}

void Pickup::apply(Aircraft& player) const
{
  Table[mType].action(player);
}

std::vector<PickupData> initializePickupData()
{
  std::vector<PickupData> data(Pickup::Count);

  data[Pickup::HealthRefill].texture  = Textures::HealthRefill;
  data[Pickup::MissileRefill].texture = Textures::MissileRefill;
  data[Pickup::FireSpread].texture    = Textures::FireSpread;
  data[Pickup::FireRate].texture      = Textures::FireRate;

  data[Pickup::HealthRefill].action   = std::bind(&Aircraft::modifyHitpoints, _1, 25);
  data[Pickup::MissileRefill].action  = std::bind(&Aircraft::modifyMissileCount, _1, 3);
  data[Pickup::FireSpread].action     = std::bind(&Aircraft::modifyFireSpread, _1);
  data[Pickup::FireRate].action       = std::bind(&Aircraft::modifyFireRate, _1);

  return data;
}

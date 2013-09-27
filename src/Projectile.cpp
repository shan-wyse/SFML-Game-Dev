#include "Projectile.hpp"

Projectile::Projectile(Type type, const TextureManager& textures)
: Entity(1)
, mType(type)
, mSprite(textures.getResource(Table[type].texture))
{
  mSprite.setCenter(mSprite.getLocalBounds() / 2.f, mSprite.getLocalBounds() / 2.f);
}

void Projectile::updateCurrent(sf::Time delta, CommandQueue& commands)
{
  if (isGuided) {
    const float approachRate = 200.f;

    sf::Vecot2f newVelocity = unitVector(approachRate * delta.asSeconds() * mTargetDirection + getVelocity());
    newVelocity *= getMaxSpeed();
    setVelocity(newVelocity);

    float angle = std::atan2(newVelocity.y, newVelocity.x);
    setRotation(toDegree(angle) + 90.f);
  }

  Entity::updateCurrent(delta, commands);
}

bool Projectile::isGuided() const { return mType == Missile; }

void Projectile::guideTowards(sf::Vector2f position)
{
  assert (isGuided());
  mTargetDirection = unitVector(position - getWorldPosition());
}

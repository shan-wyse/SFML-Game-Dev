#include <cmath>
#include <cassert>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Projectile.hpp"
#include "DataTables.hpp"
#include "ResourceManager.hpp"

namespace { const std::vector<ProjectileData> Table = initializeProjectileData(); }

Projectile::Projectile(Type type, const TextureManager& textures)
: Entity(1)
, mType(type)
, mSprite(textures.getResource(Table[type].texture))
, mTargetDirection()
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

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(mSprite, states);
}

unsigned int Projectile::getCategory() const
{
  if (mType == EnemyBullet)
    return Category::EnemyProjectile;
  else
    return Category::AlliedProjectile;
}

sf::FloatRect Projectile::getBoudningRect() const
{
  return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

float Projectile::getMaxSpeed() const { return Table[mType].speed; }

int Projectile::getDamage() const { return Table[mType].damage; }

bool Projectile::isGuided() const { return mType == Missile; }

void Projectile::guideTowards(sf::Vector2f position)
{
  assert (isGuided());
  mTargetDirection = unitVector(position - getWorldPosition());
}

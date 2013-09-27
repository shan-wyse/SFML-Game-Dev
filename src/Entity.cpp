#include "Entity.hpp"

Entity::Entity(int hitpoints)
: mVelocity()
, mHitpoints(hitpoints)
, bDestroyed(false)
{
  // empty
}

void Entity::setVelocity(sf::Vector2f velocity)
{
  mVelocity = velocity;
}

void Entity::setVelocity(float xVel, float yVel)
{
  mVelocity.x = xVel;
  mVelocity.y = yVel;
}

void Entity::accelerate(sf::Vector2f velocity)
{
  mVelocity += velocity;
}

void Entity::accelerate(float xVel, float yVel)
{
  mVelocity.x += xVel;
  mVelocity.y += yVel;
}

sf::Vector2f Entity::getVelocity() const
{
  return  mVelocity;
}

void Entity::modifyHitpoints(int hitpoints)
{
  mHitpoints += hitpoints;
}

void Entity::destroy()
{
  mHitpoints = 0;
}

int Entity::getHitpoints() const { return mHitpoints; }
bool Entity::isDestroyed() const { return bDestroyed; }

void Entity::updateCurrent(sf::Time delta)
{
  move(mVelocity * delta.asSeconds());
}

bool Entity::isDestroyed() const
{
  return mHitpoints <= 0;
}

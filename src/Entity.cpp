#include "Entity.hpp"

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

void Entity::updateCurrent(sf::Time delta)
{
  move(mVelocity * delta.asSeconds());
}
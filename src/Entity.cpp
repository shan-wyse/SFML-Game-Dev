#include <SFML/Graphics.hpp>
#include "Entity.hpp"

void Entity::setVelocity(sf::Vector2f velocity)
{
  mVelocity       = velocity;
}

void Entity::setVelocity(float xVel, float yVel)
{
  mVelocity.x     = xVel;
  mVelocity.y     = yVel;
}

sf::Vector2f Entity::getVelocity() const
{
  return          mVelocity;
}

void Entity::updateCurrent(sf::Time dt)
{
  move(mVelocity * dt.asSeconds());
}
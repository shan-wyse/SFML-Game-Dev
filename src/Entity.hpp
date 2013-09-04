#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity
{
public:
  void            setVelocity(sf::Vector2f velocity);
  void            setVelocity(float xVel, float yVel);
  sf::Vector2f    getVelocity() const;

private:
  sf::Vector2f    mVelocity;
};

#endif
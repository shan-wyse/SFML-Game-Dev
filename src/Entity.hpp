#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "SceneNode.hpp"

class Entity : public SceneNode
{
public:
  void            setVelocity(sf::Vector2f velocity);
  void            setVelocity(float xVel, float yVel);
  sf::Vector2f    getVelocity() const;

private:
  virtual void    updateCurrent(sf::Time dt);
  
  sf::Vector2f    mVelocity;
};

#endif // ENTITY_HPP
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "SceneNode.hpp"

class Entity : public SceneNode
{
public:
  explicit        Entity(int hitpoints);

  void            setVelocity(sf::Vector2f velocity);
  void            setVelocity(float xVel, float yVel);
  void            accelerate(sf::Vector2f velocity);
  void            accelerate(float xVel, float yVel);

  sf::Vector2f    getVelocity() const;

  void            modifyHitpoints(int hitpoints);
  void            repair(int hitpoints);
  void            damage(int hitpoints);
  void            destroy();

  int             getHitpoints() const;
  bool            isDestroyed() const;

protected:
  virtual void    updateCurrent(sf::Time delta, CommandQueue& commands);

private:

  sf::Vector2f    mVelocity;
  int             mHitpoints;
};

#endif // ENTITY_HPP

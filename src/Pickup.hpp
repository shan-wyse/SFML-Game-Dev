#ifndef PICKUP_HPP
#define PICKUP_HPP

#include "Entity.hpp"

class Pickup : public Entity
{
public:
  enum                      Type { HealthRefill, MissileRefill, FireSpread, FireRate, Count };

                            Pickup(Type type, const TextureManager& textures);

  virtual unsigned int      getCategory() const;
  virtual sf::FloatRect     getBoundingRect() const;

  void                      apply(Aircraft& player) const;

protected:
  virtual void              drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
  Type                      mType;
  sf::Sprite                mSprite;
};

#endif // PICKUP_HPP

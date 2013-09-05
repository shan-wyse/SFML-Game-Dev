#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include "Entity.hpp"

class Aircraft : public Entity
{
public:
  enum Type { Eagle, Raptor };
  explicit          Aircraft(Type type, const TextureManager& textures);
  virtual void      drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
  Type              mType;
  sf::Sprite        mSprite;
};

#endif
#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include <SFML/Graphics/Sprite.hpp>
#include "ResourceIdentifiers.hpp"
#include "Entity.hpp"

class Aircraft : public Entity
{
public:
  enum class Type         { Eagle, Raptor };

                          Aircraft(Type type, const TextureManager& textures);
  virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
  virtual unsigned int    getCategory() const;

private:
  Textures::Id            toTextureId(Aircraft::Type type);

  Type                    mType;
  sf::Sprite              mSprite;
};

#endif // AIRCRAFT_HPP

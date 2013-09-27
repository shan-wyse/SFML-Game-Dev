#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include "ResourceIdentifiers.hpp"
#include "Entity.hpp"
#include "TextNode.hpp"

struct Direction
{
                          Direction(float distance, float angle);
  float                   distance;
  float                   angle;
};

class Aircraft : public Entity
{
public:
  enum Type               { Eagle, Raptor, Count };

                          Aircraft(Type type, const TextureManager& textures);
  void                    update(sf::Time delta);
  virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
  virtual unsigned int    getCategory() const;

private:
  Textures::Id            toTextureId(Aircraft::Type type);

  Type                    mType;
  sf::Sprite              mSprite;
  std::unique_ptr<TextNode>     mHealthDisplay;
  float                   mTravelledDistance;
  size_t                  mDirectionIndex;
};

struct SpawnPoint
{
                          SpawnPoint(Aircraft::Type type, float xPos, float yPos);
  Aircraft::Type          type;
  float                   xPos;
  float                   yPos;
};

#endif // AIRCRAFT_HPP

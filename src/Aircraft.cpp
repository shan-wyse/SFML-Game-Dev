#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Aircraft.hpp"

Aircraft::Aircraft(Type type, const TextureManager& textures)
: mType(type)
, mSprite(textures.getResource(toTextureId(type)))
{
  sf::FloatRect bounds = mSprite.getLocalBounds();
  mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(mSprite, states);
}

Textures::Id Aircraft::toTextureId(Aircraft::Type type)
{
  switch (type) {
    case Aircraft::Type::Eagle:
      return Textures::Id::Eagle;
    case Aircraft::Type::Raptor:
      return Textures::Id::Raptor;
  }
}
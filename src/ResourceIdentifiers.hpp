#ifndef RESOURCE_IDENTIFIERS_HPP
#define RESOURCE_IDENTIFIERS_HPP

namespace Textures
{
  enum class Id { Eagle, Raptor, Desert };
}

template <typename Resource, typename Identifier>
class ResourceManager;

typedef ResourceManager<sf::Texture, Textures::Id> TextureManager;

#endif // RESOURCE_IDENTIFIERS_HPP
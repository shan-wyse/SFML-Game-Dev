#ifndef RESOURCE_IDENTIFIERS_HPP
#define RESOURCE_IDENTIFIERS_HPP

namespace Textures
{
  enum ID { Eagle, Raptor, Desert };
}

template <typename Resource, typename Identifier>
class ResourceManager;

typedef ResourceManager<sf::Texture, Textures::ID> TextureManager;

#endif // RESOURCE_IDENTIFIERS_HPP
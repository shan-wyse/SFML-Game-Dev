#ifndef RESOURCE_IDENTIFIERS_HPP
#define RESOURCE_IDENTIFIERS_HPP

namespace sf { class Texture; class Font; }

namespace Textures
{
  enum class Id { Eagle, Raptor, Desert, TitleScreen };
}

namespace Fonts
{
  enum Id { Main }; // CHANGE
}

template <typename Resource, typename Identifier>
class ResourceManager;

typedef ResourceManager<sf::Texture, Textures::Id> TextureManager;
typedef ResourceManager<sf::Font, Fonts::Id> FontManager;

#endif // RESOURCE_IDENTIFIERS_HPP

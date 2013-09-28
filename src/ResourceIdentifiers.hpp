#ifndef RESOURCE_IDENTIFIERS_HPP
#define RESOURCE_IDENTIFIERS_HPP

namespace sf { class Texture; class Font; }

namespace Textures
{
  enum class Id {
    Eagle,
    Raptor,
    Avenger,
    Desert,
    TitleScreen,
    ButtonDeselected,
    ButtonSelected,
    ButtonPressed,
    Bullet,
    Missile,
    HealthRefill,
    MissileRefill,
    FireSpread,
    FireRate
  };
}

namespace Fonts
{
  enum class Id { Main }; // CHANGE
}

template <typename Resource, typename Identifier>
class ResourceManager;

typedef ResourceManager<sf::Texture, Textures::Id> TextureManager;
typedef ResourceManager<sf::Font, Fonts::Id> FontManager;

#endif // RESOURCE_IDENTIFIERS_HPP

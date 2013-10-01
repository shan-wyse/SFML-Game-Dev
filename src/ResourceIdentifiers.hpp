#ifndef RESOURCE_IDENTIFIERS_HPP
#define RESOURCE_IDENTIFIERS_HPP

namespace sf { class Texture; class Font; class Shader; }

namespace Textures
{
  enum class Id {
    Entities,
    Jungle,
    TitleScreen,
    Buttons,
    Explosion,
    Particle,
    FinishLine
  };
}

namespace Shaders
{
  enum Id {
    BrightnessPass,
    DownSamplePass,
    GaussianBlurPass,
    AddPass
  };
}

namespace Fonts
{
  enum class Id { Main }; // CHANGE
}

namespace Music
{
  enum Id {
    MenuTheme,
    MissionTheme
  };
}

template <typename Resource, typename Identifier>
class ResourceManager;

typedef ResourceManager<sf::Texture, Textures::Id> TextureManager;
typedef ResourceManager<sf::Shader, Shaders::Id> ShaderManager;
typedef ResourceManager<sf::Font, Fonts::Id> FontManager;

#endif // RESOURCE_IDENTIFIERS_HPP

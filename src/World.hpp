#ifndef WORLD_HPP
#define WORLD_HPP

#include <array>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "ResourceManager.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "Aircraft.hpp"

class World : sf::NonCopyable
{
public:
  explicit                              World(sf::RenderWindow& window);
  void                                  update(sf::Time dt);
  void                                  draw();

private:
  enum /*class*/                            Layer { Background, Foreground, LayerCount }; // INVESTIGATE

  void                                  loadTextures();
  void                                  buildScene();

  sf::RenderWindow&                     mWindow;
  sf::View                              mWorldView;
  TextureManager                        mTextures;
  SceneNode                             mSceneGraph;
  std::array<SceneNode*, 3>     mSceneLayers; // INVESTIGATE
  sf::FloatRect                         mWorldBounds;
  sf::Vector2f                          mSpawnPosition;
  float                                 mScrollSpeed;
  Aircraft*                             mPlayerAircraft;
};

#endif // WORLD_HPP
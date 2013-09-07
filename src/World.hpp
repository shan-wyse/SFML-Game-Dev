#ifndef WORLD_HPP
#define WORLD_HPP

#include <array>
#include <SFML/Graphics.hpp>
#include "ResourceManager.hpp"
#include "SceneNode.hpp"
#include "Aircraft.hpp"

class World : sf::NonCopyable
{
public:
  explicit                              World(sf::RenderWindow& window);
  void                                  update(sf::Time dt);
  void                                  draw();

private:
  enum class                            Layer { Background, Foreground, LayerCount };

  void                                  loadTextures();
  void                                  buildScene();

  sf::RenderWindow&                     mWindow;
  sf::View                              mWorldView;
  TextureManager                        mTextures;
  SceneNode                             mSceneGraph;
  std::array<SceneNode, LayerCount>     mSceneLayers;
  sf::FloatRect                         mWorldBounds;
  sf::Vector2f                          mSpawnPosition;
  float                                 mScrollSpeed;
  Aircraft*                             mPlayerAircraft;
};

#endif
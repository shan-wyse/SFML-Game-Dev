#ifndef WORLD_HPP
#define WORLD_HPP

#include <array>
#include <queue>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "ResourceManager.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "Command.hpp"
#include "CommandQueue.hpp"
#include "Aircraft.hpp"

class World : sf::NonCopyable
{
public:
  explicit                              World(sf::RenderWindow& window, FontManager& fonts);
  void                                  update(sf::Time delta);
  void                                  draw(); // render
  CommandQueue&                         getCommandQueue();

  bool                                  hasAlivePlayer() const;
  bool                                  hasPlayerReachedEnd() const;

private:
  enum                                  Layer { Background, Foreground, LayerCount };

  struct                                SpawnPoint
                                        {
                                          SpawnPoint(Aircraft::Type type, float xPos, float yPos);

                                          Aircraft::Type type;
                                          float xPos;
                                          float yPos;
                                        };

  void                                  loadTextures();
  void                                  adaptPlayerPosition();
  void                                  adaptPlayerVelocity();
  void                                  processCollisions();

  void                                  buildScene();
  void                                  addEnemy(Aircraft::Type type, float relX, float relY);
  void                                  addEnemies(); // check position ^^^^^
  void                                  spawnEnemies();
  void                                  destroyEntitiesOutsideView();
  void                                  guideMissiles();

  sf::FloatRect                         getViewBounds() const;
  sf::FloatRect                         getBattlefieldBounds() const;

  sf::RenderWindow&                     mWindow;
  sf::View                              mWorldView;
  TextureManager                        mTextures;
  FontManager&                          mFonts;

  SceneNode                             mSceneGraph;
  std::array<SceneNode*, LayerCount>    mSceneLayers;
  CommandQueue                          mCommandQueue;

  sf::FloatRect                         mWorldBounds;
  sf::Vector2f                          mSpawnPosition;
  float                                 mScrollSpeed;
  Aircraft*                             mPlayerAircraft;

  std::vector<SpawnPoint>               mEnemySpawnPoints;
  std::vector<Aircraft*>                mActiveEnemies;
};

#endif // WORLD_HPP

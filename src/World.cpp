#include <cmath>
#include <SFML/Graphics/RenderWindow.hpp>
#include "World.hpp"

World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures()
, mSceneGraph()
, mSceneLayers()
, mCommandQueue()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 20000.f)
, mSpawnPosition(mWorldView.getSize().x / 2, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, mScrollSpeed(-600.f)
, mPlayerAircraft(nullptr)
{
  loadTextures();
  buildScene();

  mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time delta)
{
  mWorldView.move(0.f, mScrollSpeed * delta.asSeconds());
  mPlayerAircraft->setVelocity(0.f, 0.f);

  while (!mCommandQueue.isEmpty())
    mSceneGraph.onCommand(mCommandQueue.pop(), delta);

  adaptPlayerVelocity();

  mSceneGraph.update(delta);
  adaptPlayerPosition();
}

void World::draw()
{
  mWindow.setView(mWorldView);
  mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
  return mCommandQueue;
}

void World::loadTextures()
{
  mTextures.loadResource(Textures::Id::Eagle, "media/textures/eagle.png");
  mTextures.loadResource(Textures::Id::Raptor, "media/textures/raptor.png");
  mTextures.loadResource(Textures::Id::Desert, "media/textures/desert.png");
}

void World::buildScene()
{
  for (std::size_t i = 0; i < LayerCount; i++) {
    SceneNode::NodePtr layer(new SceneNode());
    mSceneLayers[i] = layer.get();

    mSceneGraph.attachChild(std::move(layer));
  }

  sf::Texture& texture = mTextures.getResource(Textures::Id::Desert);
  sf::IntRect textureRect(mWorldBounds);
  texture.setRepeated(true);

  std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
  backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
  mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

  std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Type::Eagle, mTextures));
  mPlayerAircraft = leader.get();
  mPlayerAircraft->setPosition(mSpawnPosition);
  mSceneLayers[Foreground]->attachChild(std::move(leader));
}

// CHNAGE BELOW

void World::adaptPlayerPosition()
{
  // Keep player's position inside the screen bounds, at least borderDistance units from the border
  sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
  const float borderDistance = 40.f;

  sf::Vector2f position = mPlayerAircraft->getPosition();
  position.x = std::max(position.x, viewBounds.left + borderDistance);
  position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
  position.y = std::max(position.y, viewBounds.top + borderDistance);
  position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
  mPlayerAircraft->setPosition(position);
}

void World::adaptPlayerVelocity()
{
  sf::Vector2f velocity = mPlayerAircraft->getVelocity();

  // If moving diagonally, reduce velocity (to have always same velocity)
  if (velocity.x != 0.f && velocity.y != 0.f)
    mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));

  // Add scrolling velocity
  mPlayerAircraft->accelerate(0.f, mScrollSpeed);
}

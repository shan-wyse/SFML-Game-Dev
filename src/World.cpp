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

  sf::Vector2f velocity = mPlayerAircraft->getVelocity();

  if (velocity.x != 0.f && velocity.y != 0.f)
    mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));

  mPlayerAircraft->accelerate(0.f, mScrollSpeed);

  mSceneGraph.update(delta);

  sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
  const float borderDistance = 40.f;

  sf::Vector2f position = mPlayerAircraft->getPosition();

  position.x = std::max(poition.x, viewBounds.left + borderDistance);
  position.x = std::min(poition.x, viewBounds.left - borderDistance);
  position.x = std::max(poition.y, viewBounds.top + borderDistance);
  position.x = std::min(poition.y, viewBounds.top - borderDistance);

  mPlayerAircraft->setPosition(position);
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
  mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
  mSceneLayers[Foreground]->attachChild(std::move(leader));

  std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Type::Raptor, mTextures));
  leftEscort->setPosition(-80.f, 50.f);
  mPlayerAircraft->attachChild(std::move(leftEscort));

  std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Type::Raptor, mTextures));
  rightEscort->setPosition(80.f, 50.f);
  mPlayerAircraft->attachChild(std::move(rightEscort));
}

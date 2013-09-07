#include "World.hpp"

World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
, mSpawnPosition(mWorldView.getSize().x / 2, mWorldBounds.height - mWorldView.getSize() / 2.f)
, mPlayerAircraft(nullptr)
{
  loadTextures();
  buildScene();

  mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
  mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

  sf::Vector2f position = mPlayerAircraft->getPosition();
  sf::Vector2f velocity = mPlayerAircraft->getVelocity();

  if (position.x <= mWorldBounds.left + 150 || position.x >= mWorldBounds.left + mWorldBounds.width - 150) {
    velocity.x = -velocity.x;
    mPlayerAircraft->setVelocity(velocity);
  }

  mSceneGraph.update(dt);
}

void World::draw()
{
  mWindow.setView(mWorldView);
  mWindow.draw(mSceneGraph);
}

void World::loadTextures()
{
  mTextures.load(Textures::Eagle, "media/textures/eagle.png");
  mTextures.load(Textures::Raptor, "media/textures/raptor.png");
  mTextures.load(Textures::Desert, "media/textures/desert.png");
}

void World::buildScene()
{
  for (SceneNode layer : mSceneLayers) {
    SceneNode::NodePtr node(new SceneNode());
    layer = node.get();

    mSceneGraph.attachChild(std::move(node));
  }

  sf::Texture& texture = mTextures.get(Textures::Desert);
  sf::IntRect textureRect(mWorldBounds);
  texture.setRepeated(true);

  std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
  backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
  mSceneLayers[Layer::Background]->attachChild(std::move(backgroundSprite));

  std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextures));
  mPlayerAircraft = leader.get();
  mPlayerAircraft->setPosition(mSpawnPosition);
  mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
  mSceneLayers[Layer::Foreground]->attachChild(std::move(leader));

  std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Raptor, mTextures));
  leftEscort->setPosition(-80.f, 50.f);
  mPlayerAircraft->attachChild(std::move(leftEscort));

  std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Raptor, mTextures));
  rightEscort->setPosition(80.f, 50.f);
  mPlayerAircraft->attachChild(std::move(rightEscort));
}
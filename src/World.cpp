#include <cmath>
#include <algorithm>
#include <limits>
// #include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "World.hpp"
#include "Projectile.hpp"
#include "Pickup.hpp"
#include "TextNode.hpp"
#include "ParticleNode.hpp"
#include "SoundNode.hpp"
#include <iostream>

World::World(sf::RenderTarget& outputTarget, FontManager& fonts, SoundPlayer& soundPlayer)
: mTarget(outputTarget)
, mSceneTexture()
, mFonts(fonts)
, mSoundPlayer(soundPlayer)
, mWorldView(outputTarget.getDefaultView())
, mTextures()
, mSceneGraph()
, mSceneLayers()
// , mCommandQueue()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 20000.f)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, mScrollSpeed(-100.f)
, mPlayerAircraft(nullptr)
, mEnemySpawnPoints()
, mActiveEnemies()
{
  std::cout << "HU";
  mSceneTexture.create(mTarget.getSize().x, mTarget.getSize().y);

  loadTextures();
  buildScene();

  mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time delta)
{
  mWorldView.move(0.f, mScrollSpeed * delta.asSeconds());
  mPlayerAircraft->setVelocity(0.f, 0.f);

  destroyEntitiesOutsideView();
  guideMissiles();

  while (!mCommandQueue.isEmpty())
    mSceneGraph.onCommand(mCommandQueue.pop(), delta);

  adaptPlayerVelocity();
  processCollisions();

  mSceneGraph.removeWrecks();
  spawnEnemies();

  mSceneGraph.update(delta, mCommandQueue);
  adaptPlayerPosition();

  updateSounds();
}

void World::draw()
{
  if (PostEffect::isSupported()) {
    mSceneTexture.clear();
    mSceneTexture.setView(mWorldView);
    mSceneTexture.draw(mSceneGraph);
    mSceneTexture.display();
    mBloomEffect.apply(mSceneTexture, mTarget);
  } else {
    mTarget.setView(mWorldView);
    mTarget.draw(mSceneGraph);
  }
}

CommandQueue& World::getCommandQueue()
{
  return mCommandQueue;
}

bool World::hasAlivePlayer() const { return !mPlayerAircraft->isMarkedForRemoval(); }

bool World::hasPlayerReachedEnd() const { return !mWorldBounds.contains(mPlayerAircraft->getPosition()); }

void World::loadTextures()
{
  mTextures.loadResource(Textures::Id::Entities, "media/textures/entities.png");
  mTextures.loadResource(Textures::Id::Jungle, "media/textures/jungle.png");
  mTextures.loadResource(Textures::Id::Explosion, "media/textures/explosion.png");
  mTextures.loadResource(Textures::Id::Particle, "media/textures/particle.png");
  mTextures.loadResource(Textures::Id::FinishLine, "media/textures/finish_line.png");
}

void World::buildScene()
{
  for (std::size_t i = 0; i < LayerCount; i++) {
    Category::Type category = (i == Foreground) ? Category::SceneAirLayer : Category::None;
    SceneNode::NodePtr layer(new SceneNode(category));
    mSceneLayers[i] = layer.get();

    mSceneGraph.attachChild(std::move(layer));
  }

  sf::Texture& jungleSprite = mTextures.getResource(Textures::Id::Jungle);
  jungleSprite.setRepeated(true);

  float viewHeight = mWorldView.getSize().y;
  sf::IntRect textureRect(mWorldBounds);
  textureRect.height += static_cast<int> (viewHeight);

  std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(jungleSprite, textureRect));
  backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top - viewHeight);
  mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

  sf::Texture& finishLineTexture = mTextures.getResource(Textures::Id::FinishLine);
  std::unique_ptr<SpriteNode> finishLineSprite(new SpriteNode(finishLineTexture));
  finishLineSprite->setPosition(0.f, -76.f);
  mSceneLayers[Background]->attachChild(std::move(finishLineSprite));

  std::unique_ptr<ParticleNode> smokeNode(new ParticleNode(Particle::Smoke, mTextures));
  mSceneLayers[Foreground]->attachChild(std::move(smokeNode)); // lower foreground

  std::unique_ptr<ParticleNode> propellantNode(new ParticleNode(Particle::Propellant, mTextures));
  mSceneLayers[Foreground]->attachChild(std::move(propellantNode)); // lower foreground

  std::unique_ptr<SoundNode> soundNode(new SoundNode(mSoundPlayer));
  mSceneGraph.attachChild(std::move(soundNode));

  std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Type::Eagle, mTextures, mFonts));
  mPlayerAircraft = player.get();
  mPlayerAircraft->setPosition(mSpawnPosition);
  mSceneLayers[Foreground]->attachChild(std::move(player));

  addEnemies();
}

void World::addEnemies()
{
  addEnemy(Aircraft::Raptor,    0.f,  500.f);
  addEnemy(Aircraft::Raptor,    0.f, 1000.f);
  addEnemy(Aircraft::Raptor, +100.f, 1100.f);
  addEnemy(Aircraft::Raptor, -100.f, 1100.f);
  addEnemy(Aircraft::Avenger, -70.f, 1400.f);
  addEnemy(Aircraft::Avenger, -70.f, 1600.f);
  addEnemy(Aircraft::Avenger, -70.f, 1400.f);
  addEnemy(Aircraft::Avenger, -70.f, 1600.f);

  for (int i = 0; i < 20000; i = i + 1000) {
    addEnemy(Aircraft::Raptor,    0.f,  500.f + i);
    addEnemy(Aircraft::Raptor,    0.f, 1000.f + i);
    addEnemy(Aircraft::Raptor, +100.f, 1100.f + i);
    addEnemy(Aircraft::Raptor, -100.f, 1100.f + i);
    addEnemy(Aircraft::Avenger,  -70.f, 1400.f + i);
    addEnemy(Aircraft::Avenger,  -70.f, 1600.f + i);
    addEnemy(Aircraft::Avenger,  -70.f, 1400.f + i);
    addEnemy(Aircraft::Avenger,  -70.f, 1600.f + i);
  }

  std::sort(mEnemySpawnPoints.begin(), mEnemySpawnPoints.end(), [] (SpawnPoint a, SpawnPoint b)
  {
    return a.yPos < b.yPos;
  } );
}

void World::addEnemy(Aircraft::Type type, float relX, float relY)
{
  SpawnPoint spawn(type, mSpawnPosition.x + relX, mSpawnPosition.y - relY);
  mEnemySpawnPoints.push_back(spawn);
}

// CHNAGE BELOW

void World::adaptPlayerPosition()
{
  // Keep player's position inside the screen bounds, at least borderDistance units from the border
  sf::FloatRect viewBounds = getViewBounds();
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

bool matchesCategories(SceneNode::NodePair& colliders, Category::Type typeA, Category::Type typeB)
{
  unsigned int categoryA = colliders.first->getCategory();
  unsigned int categoryB = colliders.second->getCategory();

  if (typeA & categoryA && typeB & categoryB)
    return true;
  else if (typeA & categoryB && typeB & categoryA) {
    std::swap(colliders.first, colliders.second);
    return true;
  } else
    return false;
}

void World::spawnEnemies()
{
  while (!mEnemySpawnPoints.empty() && mEnemySpawnPoints.back().yPos > getBattlefieldBounds().top) {
    SpawnPoint spawn = mEnemySpawnPoints.back();

    std::unique_ptr<Aircraft> enemy(new Aircraft(spawn.type, mTextures, mFonts));
    enemy->setPosition(spawn.xPos, spawn.yPos);
    enemy->setRotation(180.f);

    mSceneLayers[Foreground]->attachChild(std::move(enemy));
    mEnemySpawnPoints.pop_back();
  }
}

void World::guideMissiles()
{
  Command enemyCollector;
  enemyCollector.category = Category::EnemyAircraft;
  enemyCollector.action = derivedAction<Aircraft> ([this] (Aircraft& enemy, sf::Time)
  {
    if (!enemy.isDestroyed()) mActiveEnemies.push_back(&enemy);
  } );

  Command missileGuider;
  missileGuider.category = Category::AlliedProjectile;
  missileGuider.action = derivedAction<Projectile>([this] (Projectile& missile, sf::Time)
  {
    if (!missile.isGuided()) return;

    float minDistance = std::numeric_limits<float>::max();
    Aircraft* closestEnemy = nullptr;

    for (Aircraft* enemy : mActiveEnemies) {
      float enemyDistance = distance(missile, *enemy);

      if (enemyDistance < minDistance) {
        closestEnemy = enemy;
        minDistance = enemyDistance;
      }
    }

    if (closestEnemy)
      missile.guideTowards(closestEnemy->getWorldPosition());
  } );

  mCommandQueue.push(enemyCollector);
  mCommandQueue.push(missileGuider);
  mActiveEnemies.clear();
}

void World::processCollisions()
{
  std::set<SceneNode::NodePair> collisionPairs;
  mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

  for (SceneNode::NodePair pair : collisionPairs) {
    if (matchesCategories(pair, Category::PlayerAircraft, Category::EnemyAircraft)) {
      auto& player = static_cast<Aircraft&> (*pair.first);
      auto& enemy = static_cast<Aircraft&> (*pair.second);

      player.modifyHitpoints(-enemy.getHitpoints());
      enemy.destroy();
    } else if (matchesCategories(pair, Category::PlayerAircraft, Category::Pickup)) {
      auto& player = static_cast<Aircraft&> (*pair.first);
      auto& pickup = static_cast<Pickup&> (*pair.second);

      pickup.apply(player);
      pickup.destroy();
      player.playLocalSound(mCommandQueue, SoundEffects::CollectPickup);
    } else if (matchesCategories(pair, Category::EnemyAircraft, Category::AlliedProjectile) ||
               matchesCategories(pair, Category::PlayerAircraft, Category::EnemyProjectile)) {
      auto& aircraft = static_cast<Aircraft&> (*pair.first);
      auto& projectile = static_cast<Projectile&> (*pair.second);

      aircraft.modifyHitpoints(-projectile.getDamage());
      projectile.destroy();
    }
  }
}

void World::destroyEntitiesOutsideView()
{
  Command command;
  command.category = Category::Projectile | Category::EnemyAircraft;
  command.action = derivedAction<Entity> ([this] (Entity& entity, sf::Time)
  {
    if (!getBattlefieldBounds().intersects(entity.getBoundingRect()))
      entity.destroy();
  } );

  mCommandQueue.push(command);
}

sf::FloatRect World::getViewBounds() const
{
  return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
}

sf::FloatRect World::getBattlefieldBounds() const
{
  sf::FloatRect bounds = getViewBounds();
  bounds.top -= 100.f;
  bounds.height += 100.f;

  return bounds;
}

void World::updateSounds()
{
  mSoundPlayer.setListenerPosition(mPlayerAircraft->getWorldPosition());
  mSoundPlayer.removeStoppedSounds();
}

World::SpawnPoint::SpawnPoint(Aircraft::Type type, float xPos, float yPos)
: type(type)
, xPos(xPos)
, yPos(yPos)
{
  // empty
}

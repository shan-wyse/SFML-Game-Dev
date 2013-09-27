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

  destroyEntitiesOutsideView();
  guideMissiles();

  while (!mCommandQueue.isEmpty())
    mSceneGraph.onCommand(mCommandQueue.pop(), delta);

  adaptPlayerVelocity();

  processCollisions();
  mSceneGraph.removeWrecks();
  spawnEnemies();

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

void World::spawnEnemies()
{
  while (!mEnemySpawnPoints.empty() && mEnemySpawnPoints.back().y > getSpawnBounds().top) {
    SpawnPoint spawn = mEnemySpawnPoints.back();

    std::unique_ptr<Aircraft> enemy(new Aircraft(spawn.type, mTextures, mFonts));
    enemy->setPosition(spawn.x, spawn.y);
    enemy->setRepeated(180.f);

    mSceneLayers[Foreground]->attachChild(std::move(enemy));
    mEnemySpawnPoints.pop_back();
  }
}

void World::addEnemies()
{
  addEnemy(Aircraft::Raptor,    0.f,    500.f);
  addEnemy(Aircraft::Avenger, -70.f,   1400.f);

  std::sort(mEnemySpawnPoints.begin(), mEnemySpawnPoints.end(), [] (SpawnPoint a, SpawnPoint b)
  {
    return a.y < b.y;
  });
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
  missileGuider.category = Projectile::AilliedProjectile;
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
  std::set<SceneNode::Pair> collisionPairs;
  mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

  for (SceneNode::Pair pair : collision pairs) {
    if (matchesCategories(pair, Category::PlayerAircraft, Category::EnemyAircraft)) {
      auto& player = static_cast<Aircraft&> (*pair.first);
      aito& enemy = static_cast<Aircraft&> (*pair.second);

      player.modifyHitpoints(enemy.getHitpoints());
      enemy.destroy();
    }
  } else if (matchesCategories(pair, Category::PlayerAircraft, Category::Pickup)) {
    auto& player = static_cast<Aircraft&> (*pair.first);
    auto& pickup = static_cast<Pickup&> (*pair.second);

    pickup.apply(player);
    pickup.destroy();
  } else if (matchesCategories(pair, Category::EnemyAircraft, Category::AilliedProjectile) ||
             matchesCategories(pair, Category::PlayerAircraft, Category::EnemyProjectile)) {
    auto& aircraft = static_cast<Aircraft&> (*pair.first);
    auto& projectile = static_cast<Projectile&> (*pair.second);

    aircraft.modifyHitpoints(-projectile.getDamage());
    projectile.destory();
  }
}

void World::destroyEntitiesOutsideView()
{
  Command command;
  command.category = Category::Projectile | Category::EnemyAircraft;
  command.action = derivedAction<Entity> ([this] (Entity& entity, sf::Time)
  {
    if (!getBattlefieldBounds().intersects(entity.getBoundingRect()))
      entity.destory();
  } );

  mCommandQueue.push(command);
}

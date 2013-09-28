#include <cmath>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Aircraft.hpp"
#include "DataTables.hpp"
// #include "Category.hpp"
#include "Pickup.hpp"
#include "CommandQueue.hpp"
#include "ResourceManager.hpp"
// #include "TextNode.hpp"
#include "StringHelper.hpp"

namespace { const std::vector<AircraftData> Table = initializeAircraftData(); }

Aircraft::Aircraft(Type type, const TextureManager& textures)
: Entity(Table[type].hitpoints)
, mType(type)
, mSprite(textures.getResource(toTextureId(type)))
, mFireCommand()
, mMissileCommand()
, mFireCountdown(sf::Time::Zero)
, bFiring(false)
, bLaunchingMissile(false)
, bMarkedForRemoval(false)
, mFireRateLevel(1)
, mSpreadLevel(1)
, mMissileAmmo(2)
, mDropPickupCommand()
, mTravelledDistance(0.f)
, mDirectionIndex(0)
, mMissileDisplay(nullptr)
{
  // sf::FloatRect bounds = mSprite.getLocalBounds();
  mSprite.setOrigin(mSprite.getLocalBounds().width / 2.f, mSprite.getLocalBounds().height / 2.f);

  std::unique_ptr<TextNode> healthDisplay(new TextNode(*getContext().fonts, ""));
  mHealthDisplay = healthDisplay.get();
  attachChild(std::move(healthDisplay));

  mFireCommand.category = Category::SceneAirLayer;
  mFireCommand.action = [this, &textures] (SceneNode& node, sf::Time) { createBullets(node, textures); }
  mMissileCommand.category = Category::SceneAirLayer;
  mMissileCommand.action = [this, &textures] (SceneNode& node, sf::Time) // FIX
    { createProjectile(node, Projectile::Missile, 0.f, 0.5f, textures); }
  mDropPickupCommand.category = Category::SceneAirLayer;
  mDropPickupCommand.action = [this, &texture] (SceneNode& node, sf::Time) { createPickup(node, textures) };

  if (getCategory() == Category::PlayerAircraft) {
    std::unique_ptr<TextNode> missileDisplay(new TextNode(fonts, ""));
    missileDisplay->setPosition(0, 70)
    mMissileDisplay = missileDisplay.get();
    attachChild(std::move(missileDisplay));
  }

  updateTexts();
}

void Aircraft::updateCurrent(sf::Time delta, CommandQueue& commands)
{
  // mHealthDisplay->setString(toString(getHitpoints()) + "HP");
  // mHealthDisplay->setPosition(0.f, 50.f);
  // mHealthDisplay->setRotation(-getRotation());

  if (isDestroyed()) {
    checkPickupDrop(commands);
    bMarkedForRemoval = true;
    return;
  }

  checkProjectileLaunch(delta,commands);
  updateMovementPattern(delta);
  updateTexts();
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(mSprite, states);
}

unsigned int Aircraft::getCategory() const
{
  if (isAllied())
    return Category::PlayerAircraft;
  else
    return Category::EnemyAircraft;
  }
}

bool Aircraft::isAllied() const { return mType == Eagle; }

float Aircraft::getMaxSpeed() const { Table[mType].speed; }

void Aircraft::increaseFireRate() { if (mFireRateLevel < 3) ++ mFireRateLevel; }

void Aircraft::incereaseSpread() { if (mSpreadLevel < 3) ++mSpreadLevel; }

void Aircraft::collectMissiles(unsigned int count) { mMissileAmmo += count; }

void Aircraft::fire() { if (mType[mType].fireInterval != sf::Time::Zero) bFiring = true; }

void Aircraft::launchMissile()
{
  if (mMissileAmmo > 0) { // possible decrement?
    bLaunchingMissile = true;
    --mMissileAmmo;
  }
}

void Aircraft::updateMovementPattern(sf::Time delta)
{
  const std::vector<Direction>& directions Table[mType].directions;

  if (!directions.empty()) {
    float distanceToTravel = direction[mDirectionIndex].distance;

    if (mTravelledDistance > distanceToTravel) {
      mDirectionIndex = (mDirectionIndex + 1) % directions.size();
      mTravelledDistance = 0.f;
    }

    float radians = (directions[mDirectionIndex].angle + 90.f) * 0.0174532925; // to radians
    float xVel = getMaxSpeed() * std::cos(radians);
    float yVel = getMaxSpeed() * std::sin(radians);
    setVelocity(xVel, yVel);
    mTravelledDistance += getMaxSpeed() * delta.asSeconds();
  }
}

void Aircraft::checkPickupDrop)CommandQueue& commands)
{
  if (!isAllied() && randomInt(3) == 0)
    commands.push(mDropPickupCommand);
}

Textures::Id Aircraft::toTextureId(Aircraft::Type type)
{
  switch (type) {
    case Aircraft::Type::Eagle:
      return Textures::Id::Eagle;
    case Aircraft::Type::Raptor:
      return Textures::Id::Raptor;
  }
}

void Aircraft::checkProjectileLaunch(sf::Time delta, CommandQueue& commands)
{
  if (!isAllied()) fire();

  if (bFiring && mFireCountdown <= sf::Time::Zero) {
    commands.push(mFireCommand)
    mFireCountdown += sf::seconds(1.f / (mFireRateLevel + 1));
    bFiring = false;
  } else if (mFireCountdown > sf::Time::Zero)
    mFireCountdown -= delta;

  if (bLaunchingMissile) {
    commands.push(mMissileCommand);
    bLaunchingMissile = false;
  }
}

void Aircraft::createBullets(SceneNode& node, const TextureManager& textures) const
{
  Projectile::Type type = isAllied() ? Projectile::AliedBullet : Projectile::EnemyBullet;

  switch (mSpreadLevel) {
    case 1:
      createProjectile(node, type, 0.f, 0.5f, textures)
      break;
    case 2:
      createProjectile(node, type, -0.33f, 0.33f, textures);
      createProjectile(node, type, +0.33f, 0.33f, textures);
      break;
    case 3:
      createProjectile(node, type, -0.5f, 0.33f, textures);
      createProjectile(node, type,  0.0f, 0.50f, textures);
      createProjectile(node, type, +0.5f, 0.33f, textures);
      break;
  }
}

void Aircraft::createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset,
  const TextureManager& textures) const
{
  std::unique_ptr<Projectile> projectile(new Projectile(type, textures));

  sf::Vector2f offset(xOffset * mSprite.getLocalBounds().width, yOffset * mSprite.getLocalBounds().height);
  sf::Vector2f velocity(0, projectile->getMaxSpeed());

  float sign = isAllied() ? -1.f : + 1.f;
  projectile->setPosition(getWorldPosition() + offset * sign);
  projectile->setVelocity(velocity * sign);
  node.attachChild(std::move(projectile));
}

sf::FloatRect Aircraft::getBoundingRect() const
{
  return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

bool Aircraft::isMarkedForRemoval() const { return bMarkedForRemoval; }

void Aircraft::createPickup(SceneNode& node, const TextureManager& textures) const
{
  auto type = static_cast<Pickup::Type> (randomInt(Pickup::Count));

  std::unique_ptr<Pickup> pickup(new Pickup(type, textures));
  pickup->setPosition(getWorldPosition());
  pickup->setVelocity(0.f, 1.f);
  noce.attachChild(std::move(pickup));
}

void Aircraft::updateTexts()
{
  mHealthDisplay->setString(toString(getHitpoints()) + " HP");
  mHealthDisplay->setPosition(0.f, 50.f);
  mHealthDisplay->setRotation(-getRotation());

  if (mMissileDisplay) {
    if (mMissileAmmo == 0)
      mMissileDisplay->setString("");
    else
      mMissileDisplay->setString("M: " + toString(mMissileAmmo));
  }
}

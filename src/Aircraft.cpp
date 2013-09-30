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
#include "Utility.hpp"
#include "StringHelper.hpp"

namespace { const std::vector<AircraftData> Table = initializeAircraftData(); }

Aircraft::Aircraft(Type type, const TextureManager& textures, const FontManager& fonts)
: Entity(Table[type].hitpoints)
, mType(type)
, mSprite(textures.getResource(Table[type].texture), Table[type].textureRect)
, mFireCommand()
, mMissileCommand()
, mFireCountdown(sf::Time::Zero)
, bFiring(false)
, bLaunchingMissile(false)
// , bMarkedForRemoval(false)
, mFireRateLevel(1)
, mSpreadLevel(1)
, mMissileAmmo(20)
, mDropPickupCommand()
, mTravelledDistance(0.f)
, mDirectionIndex(0)
, mHealthDisplay(nullptr)
, mMissileDisplay(nullptr)
{
  // sf::FloatRect bounds = mSprite.getLocalBounds();
  mSprite.setOrigin(mSprite.getLocalBounds().width / 2.f, mSprite.getLocalBounds().height / 2.f);

  mFireCommand.category = Category::SceneAirLayer;
  mFireCommand.action = [this, &textures] (SceneNode& node, sf::Time) { createBullets(node, textures); };

  mMissileCommand.category = Category::SceneAirLayer;
  mMissileCommand.action = [this, &textures] (SceneNode& node, sf::Time) // FIX
    { createProjectile(node, Projectile::Missile, 0.f, 0.5f, textures); };

  mDropPickupCommand.category = Category::SceneAirLayer;
  mDropPickupCommand.action = [this, &textures] (SceneNode& node, sf::Time) { createPickup(node, textures); };

  std::unique_ptr<TextNode> healthDisplay(new TextNode("", fonts));
  mHealthDisplay = healthDisplay.get();
  attachChild(std::move(healthDisplay));

  if (getCategory() == Category::PlayerAircraft) {
    std::unique_ptr<TextNode> missileDisplay(new TextNode("", fonts));
    missileDisplay->setPosition(0, 70);
    mMissileDisplay = missileDisplay.get();
    attachChild(std::move(missileDisplay));
  }

  updateTexts();

  mExplosion.setFrameSize(sf::Vector2i(256, 256));
  mExplosion.setFrameCount(16);
  mExplosion.setDuration(sf::seconds(1));


}

void Aircraft::updateCurrent(sf::Time delta, CommandQueue& commands)
{
  // mHealthDisplay->setString(toString(getHitpoints()) + "HP");
  // mHealthDisplay->setPosition(0.f, 50.f);
  // mHealthDisplay->setRotation(-getRotation());

  if (isDestroyed()) {
    checkPickupDrop(commands);
    mExplosion.update(delta);
    // bMarkedForRemoval = true;
    return;
  }

  checkProjectileLaunch(delta,commands);
  updateMovementPattern(delta);
  Entity::updateCurrent(delta, commands);
  updateTexts();
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
  if (isDestroyed() && bShowExplosion)
    target.draw(mExplosion, states);
  else
    target.draw(mSprite, states);
}

unsigned int Aircraft::getCategory() const
{
  if (isAllied())
    return Category::PlayerAircraft;
  else
    return Category::EnemyAircraft;
}

bool Aircraft::isAllied() const { return mType == Eagle; }

float Aircraft::getMaxSpeed() const { return Table[mType].speed; }

void Aircraft::increaseFireRate() { if (mFireRateLevel < 10) ++ mFireRateLevel; }

void Aircraft::increaseSpread() { if (mSpreadLevel < 3) ++mSpreadLevel; }

void Aircraft::collectMissiles(unsigned int count) { mMissileAmmo += count; }

void Aircraft::fire() { if (Table[mType].fireInterval != sf::Time::Zero) bFiring = true; }

void Aircraft::launchMissile()
{
  if (mMissileAmmo > 0) { // possible decrement?
    bLaunchingMissile = true;
    --mMissileAmmo;
  }
}

void Aircraft::updateMovementPattern(sf::Time delta)
{
  const std::vector<Direction>& directions = Table[mType].directions;

  if (!directions.empty()) {
    float distanceToTravel = directions[mDirectionIndex].distance;

    if (mTravelledDistance > distanceToTravel) {
      mDirectionIndex = (mDirectionIndex + 1) % directions.size();
      mTravelledDistance = 0.f;
    }

    float radians = Utility::toRadian(directions[mDirectionIndex].angle + 90.f);
    float xVel = getMaxSpeed() * std::cos(radians);
    float yVel = getMaxSpeed() * std::sin(radians);
    setVelocity(xVel, yVel);
    mTravelledDistance += getMaxSpeed() * delta.asSeconds();
  }
}

void Aircraft::checkPickupDrop(CommandQueue& commands)
{
  if (!isAllied() && Utility::randomInt(3) == 0)
    commands.push(mDropPickupCommand);
}

void Aircraft::checkProjectileLaunch(sf::Time delta, CommandQueue& commands)
{
  if (!isAllied()) fire();

  if (bFiring && mFireCountdown <= sf::Time::Zero) {
    commands.push(mFireCommand);
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
  Projectile::Type type = isAllied() ? Projectile::AlliedBullet : Projectile::EnemyBullet;

  switch (mSpreadLevel) {
    case 1:
      createProjectile(node, type, 0.f, 0.5f, textures);
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

  sf::Vector2f offset(xOffset * mSprite.getGlobalBounds().width, yOffset * mSprite.getGlobalBounds().height);
  sf::Vector2f velocity(0, projectile->getMaxSpeed());

  float sign = isAllied() ? -1.f : +1.f;
  projectile->setPosition(getWorldPosition() + offset * sign);
  projectile->setVelocity(velocity * sign);
  node.attachChild(std::move(projectile));
}

sf::FloatRect Aircraft::getBoundingRect() const
{
  return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

bool Aircraft::isMarkedForRemoval() const { return isDestroyed() && (mExplosion.isFinished() || !bShowExplosion); }

void Aircraft::createPickup(SceneNode& node, const TextureManager& textures) const
{
  auto type = static_cast<Pickup::Type> (Utility::randomInt(Pickup::Count));

  std::unique_ptr<Pickup> pickup(new Pickup(type, textures));
  pickup->setPosition(getWorldPosition());
  pickup->setVelocity(0.f, 1.f);
  node.attachChild(std::move(pickup));
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

void Aircraft::updateRollAnimation()
{
  if (Table[mType].hasRollAnimation) {
    sf::IntRect textureRect = Table[mType].textureRect;

    if (getVelocity().x < 0.f)
      textureRect.left += textureRect.width;
    else if (getVelocity().x > 0.f)
      textureRect.left += 2 * textureRect.width;

    mSprite.setTextureRect(textureRect);
  }
}

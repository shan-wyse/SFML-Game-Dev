#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

// #include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"
#include "Command.hpp"
#include "Projectile.hpp"
#include "TextNode.hpp"
#include "Animation.hpp"

// struct Direction
// {
//                           Direction(float distance, float angle);
//   float                   distance;
//   float                   angle;
// };

class Aircraft : public Entity
{
public:
  enum Type               { Eagle, Raptor, Avenger, Count };

                          Aircraft(Type type, const TextureManager& textures, const FontManager& fonts);
  // void                    update(sf::Time delta);

  virtual void            updateCurrent(sf::Time delta, CommandQueue& commands);
  virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

  virtual unsigned int    getCategory() const;
  virtual sf::FloatRect   getBoundingRect() const;
  virtual void            remove();
  virtual bool            isMarkedForRemoval() const;

  bool                    isAllied() const;
  float                   getMaxSpeed() const;

  void                    increaseFireRate();
  void                    increaseSpread();
  void                    collectMissiles(unsigned int count);

  void                    fire();
  void                    launchMissile();

private:
  void                    updateMovementPattern(sf::Time delta);
  void                    checkPickupDrop(CommandQueue& commands);
  void                    checkProjectileLaunch(sf::Time delta, CommandQueue& commands);

  void                    createBullets(SceneNode& node, const TextureManager& textures) const;
  void                    createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset,
                              const TextureManager& textures) const; // REFACTOR, local mTextures
  void                    createPickup(SceneNode& node, const TextureManager& textures) const;

  void                    updateTexts();
  void                    updateRollAnimation();

  Textures::Id            toTextureId(Aircraft::Type type);

  Type                    mType;
  sf::Sprite              mSprite;

  Command                 mFireCommand;
  Command                 mMissileCommand;
  sf::Time                mFireCountdown;

  bool                    bFiring;
  bool                    bLaunchingMissile;
  bool                    mSpawnedPickup;
  // bool                    bMarkedForRemoval;

  int                     mFireRateLevel;
  int                     mSpreadLevel;
  int                     mMissileAmmo;

  // std::unique_ptr<TextNode>     mHealthDisplay;
  Command                 mDropPickupCommand;
  float                   mTravelledDistance;
  size_t                  mDirectionIndex;
  TextNode*               mHealthDisplay;
  TextNode*               mMissileDisplay;

  Animation               mExplosion;
  bool                    bShowExplosion;
};

// struct SpawnPoint
// {
//                           SpawnPoint(Aircraft::Type type, float xPos, float yPos);
//   Aircraft::Type          type;
//   float                   xPos;
//   float                   yPos;
// };

#endif // AIRCRAFT_HPP

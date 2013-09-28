#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

class Projectile : public Entity
{
public:
  enum                      Type { AlliedBullet, EnemyBullet, Missile, Count };

                            Projectile(Type type, const TextureManager& textures);

  void                      guideTowards(sf::Vector2f position);
  bool                      isGuided() const;

  virtual unsigned int      getCategory() const;
  virtual sf::FloatRect     getBoundingRectangle() const;
  float                     getMaxSpeed() const;
  int                       getDamage() const;

private:
  virtual void              updateCurrent(sf::Time delta, CommandQueue& commands);
  virtual void              drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

  Type                      mType;
  sf::Sprite                mSprite;
  sf::Vector2f              mTargetDirection;
};

#endif // PROJECTILE_HPP

#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Animation : public sf::Drawable, public sf::Transformable
{
public:
                        Animation();
  explicit              Animation(const sf::Texture& texture);

  void                  update(sf::Time delta);
  void                  restart();
  bool                  isFinished() const;

  void                  setTexture(const sf::Texture& texture);
  void                  setFrameSize(sf::Vector2i frameSize);
  void                  setFrameCount(std::size_t frameCount);
  void                  setDuration(sf::Time duration);
  void                  setRepeating(bool flag);

  const sf::Texture*    getTexture() const;
  sf::Vector2i          getFrameSize() const;
  std::size_t           getFrameCount() const;
  sf::Time              getDuration() const;
  bool                  isRepeating() const;

  sf::FloatRect         getLocalBounds() const;
  sf::FloatRect         getGlobalBounds() const;

private:
  void                  draw(sf::RenderTarget& target, sf::RenderStates states) const;

  sf::Sprite            mSprite;
  sf::Vector2i          mFrameSize;
  std::size_t           mFrameCount;
  std::size_t           mCurrentFrame;
  sf::Time              mDuration;
  sf::Time              mElapsedTime;
  bool                  bRepeat;
};

# endif // ANIMATION_HPP

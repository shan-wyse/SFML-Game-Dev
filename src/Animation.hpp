#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Animation : public sf::Drawable, public sf::Transformable
{
public:


  void              update(sf::Time delta);
  bool              isFinished() const;

  void              setFrameSize(sf::Vector2i frameSize);
  void              setFrameCount(std::size_t frameCount);
  void              setDuration(sf::Time duration);

private:
  void              draw(sf::RenderTarget& target, sf::RenderStates states) const;

  sf::Sprite        mSprite;
  sf::Vector2i      mFrameSize;
  std::size_t       mFrameCount;
  std::size_t       mCurrentFrame;
  sf::Time          mDuration;
  sf::Time          mElapsedTime;
  bool              bRepeat;
};

# endif // ANIMATION_HPP

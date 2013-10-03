#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Animation.hpp"

Animation::Animation()
: mSprite()
, mFrameSize()
, mFrameCount(0)
, mCurrentFrame(0)
, mDuration(sf::Time::Zero)
, mElapsedTime(sf::Time::Zero)
, bRepeat(false)
{
  // empty
}

Animation::Animation(const sf::Texture& texture)
: mSprite(texture)
, mFrameSize()
, mFrameCount(0)
, mCurrentFrame(0)
, mDuration(sf::Time::Zero)
, mElapsedTime(sf::Time::Zero)
, bRepeat(false)
{
  // empty
}


void Animation::update(sf::Time delta)
{
  sf::Time timePerFrame = mDuration / static_cast<float> (mFrameCount);
  mElapsedTime += delta;

  sf::Vector2i textureBounds(mSprite.getTexture()->getSize());
  sf::IntRect textureRect = mSprite.getTextureRect();

  if (mCurrentFrame == 0)
    textureRect = sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y);

  while (mElapsedTime >= timePerFrame && (mCurrentFrame <= mFrameCount || bRepeat)) {
    textureRect.left += textureRect.width;

    if (textureRect.left + textureRect.width >= textureBounds.x) {
      textureRect.left = 0;
      textureRect.top += textureRect.height;
    }

    mElapsedTime -= timePerFrame;

    if (bRepeat) {
      mCurrentFrame = (mCurrentFrame + 1) % mFrameCount;

      if (mCurrentFrame == 0)
        textureRect = sf::IntRect(0, 0, mFrameSize.x, mFrameSize.y);
    } else
      mCurrentFrame++;
  }

  mSprite.setTextureRect(textureRect);
}

void Animation::restart() { mCurrentFrame = 0; }
bool Animation::isFinished() const { return mCurrentFrame >= mFrameCount; }

void Animation::setTexture(const sf::Texture& texture) { mSprite.setTexture(texture); }
void Animation::setFrameSize(sf::Vector2i frameSize) { mFrameSize = frameSize; }
void Animation::setFrameCount(std::size_t frameCount) { mFrameCount = frameCount; }
void Animation::setDuration(sf::Time duration) { mDuration = duration; }
void Animation::setRepeating(bool flag) { bRepeat = flag; }

const sf::Texture* Animation::getTexture() const { return mSprite.getTexture(); }
sf::Vector2i Animation::getFrameSize() const { return mFrameSize; }
std::size_t Animation::getFrameCount() const { return mFrameCount; }
sf::Time Animation::getDuration() const { return mDuration; }
bool Animation::isRepeating() const { return bRepeat; }

sf::FloatRect Animation::getLocalBounds() const { return sf::FloatRect(getOrigin(), static_cast<sf::Vector2f> (getFrameSize())); }
sf::FloatRect Animation::getGlobalBounds() const { return getTransform().transformRect(getLocalBounds()); }

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(mSprite, states);
}

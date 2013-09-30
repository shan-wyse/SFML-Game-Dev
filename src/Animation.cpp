#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Animation.hpp"

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

bool Animation::isFinished() const { return mCurrentFrame >= mFrameCount; }

void Animation::setFrameSize(sf::Vector2i frameSize) { mFrameSize = frameSize; }
void Animation::setFrameCount(std::size_t frameCount) { mFrameCount = frameCount; }
void Animation::setDuration(sf::Time duration) { mDuration = duration; }

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(mSprite, states);
}

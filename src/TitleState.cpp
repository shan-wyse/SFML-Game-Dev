#include "TitleState.hpp"

bool TitleState::processEvent(const sf::Event& event)
{
  if (event.type == sf::Event::KeyPressed) {
    requestStatePop();
    requestStackPush(States::Menu);
  }

  return true;
}

bool TitleState::update(sf::Time delta)
{
  mTextEffectTime += delta;

  if (mTextEffectTime >= sf::seconds(0.5f)) {
    mShowText = !mShowText;
    mTextEffectTime = sf::Time::Zero;
  }

  return true;
}

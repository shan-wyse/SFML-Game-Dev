#include <SFML/Graphics/RenderWindow.hpp>
#include "TitleState.hpp"
#include "ResourceManager.hpp"

TitleState::TitleState(StateStack& stack, Context context)
: State(stack, context)
, mText()
, mShowText(true)
, mTextEffectTime(sf::Time::Zero)
{
  mBackgroundSprite.setTexture(context.textures->getResource(Textures::Id::TitleScreen));

  mText.setFont(context.fonts->getResource(Fonts::Id::Main));
  mText.setString("Press any key to start");
  mText.setOrigin(mText.getLocalBounds().width / 2.f, mText.getLocalBounds().height / 2.f);
  mText.setPosition(context.window->getView().getSize() / 2.f);
}

bool TitleState::processEvent(const sf::Event& event)
{
  if (event.type == sf::Event::KeyReleased) {
    requestStackPop();
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

void TitleState::render()
{
  sf::RenderWindow& window = *getContext().window;
  window.draw(mBackgroundSprite);

  if (mShowText)
    window.draw(mText);
}

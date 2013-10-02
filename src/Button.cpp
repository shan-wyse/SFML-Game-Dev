#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Button.hpp"
#include "ResourceManager.hpp"
#include "SoundPlayer.hpp"

namespace Gui
{

Button::Button(State::Context context)
: mCallback()
, mSprite(context.textures->getResource(Textures::Id::Buttons))
, mText("", context.fonts->getResource(Fonts::Id::Main), 16)
, mSoundPlayer(*context.soundPlayer)
, mIsToggle(false)
{
  changeTexture(Deselected);

  sf::FloatRect bounds = mSprite.getLocalBounds();
  mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

bool Button::isSelectable() const
{
  return true;
}

void Button::setSelected(bool selected)
{
  Component::setSelected(selected);
  if (selected)
    changeTexture(Selected);
  else
    changeTexture(Deselected);
}

void Button::setActive(bool active)
{
  Component::setActive(active);

  if (active) {
    Component::setActive(true);

    if (mIsToggle)
      changeTexture(Pressed);
    if (!mIsToggle)
      setActive(false);
    if (mCallback)
      mCallback();
  } else {
    if (mIsToggle) {
      if (isSelected())
        changeTexture(Selected);
      else
        changeTexture(Deselected);
    }
  }

  mSoundPlayer.play(SoundEffects::Button);
}

void Button::processEvent(const sf::Event& event)
{
  // empty
}

void Button::setCallback(Callback callback)
{
  mCallback = std::move(callback);
}

void Button::setText(const std::string& text)
{
  mText.setString(text);
  mText.setOrigin(mText.getLocalBounds().width / 2.f, mText.getLocalBounds().height / 2.f);
}

void Button::setToggle(bool toggle)
{
  mIsToggle = toggle;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(mSprite, states);
  target.draw(mText, states);
}

void Button::changeTexture(Type buttonType)
{
  sf::IntRect textureRect(0, 50 * buttonType, 200, 50);
  mSprite.setTextureRect(textureRect);
}

}

// void Button::deactivate()
// {
//   Component::deactivate(active);

//   if (mIsToggle) {
//     if (isSelected())
//       mSprite.setTexture(mSelectedTexture);
//     else
//       mSprite.setTexture(mDeselectedTexture);
//   }
// }

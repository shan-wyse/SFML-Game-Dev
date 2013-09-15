#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarger.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Button.hpp"

namespace Gui
{

Button::Button(const TextureManager& textures, const FontManager& fonts)
: mCallback()
, mDeselectedTexture(textures.getResource(Textures::Id::ButtonDeselected))
, mSelectedTexture(textures.getResource(Textures::Id::ButtonSelected))
, mPressedTexture(textures.getResource(Textures::Id::ButtonPressed))
, mSprite()
, mText("", fonts.getResource(Fonts::Main), 16)
, mIsToggle(false)
{
  mSprite.setTexture(mDeselectedTexture);

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
    mSprite.setTexture(mSelectedTexture);
  else
    mSprite.setTexture(mDeselectedTexture);
}

void Button::setActive(bool active)
{
  Component::activate(active);

  if (active) {
    if (mIsToggle)
      mSprite.setTexture(mPressedTexture);
    if (!mIsToggle)
      setActive(false);
    if (mCallback)
      mCallback();
  } else {
    if (mIsToggle) {
      if (isSelected())
        mSprite.setTexture(mSelectedTexture);
      else
        mSprite.setTexture(mDeselectedTexture);
    }
  }
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

void Button::draw(sf::RenderTarger& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(mSprite, states);
  target.draw(mText, states);
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

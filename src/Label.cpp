#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Label.hpp"

namespace Gui
{

Label::Label(const std::string& text, const FontManager& fonts)
: mText(text, fonts.getResource(Fonts::Id::Main), 16)
{
  // empty
}

bool Label::isSelectable() const
{
  return false;
}

void Label::processEvent(const sf::Event& event)
{
  // empty
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(mText, states);
}

void Label::setText(const std::string& text)
{
  mText.setString(text);
}

}

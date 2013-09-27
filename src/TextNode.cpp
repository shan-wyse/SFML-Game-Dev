#include "TextNode.hpp"

TextNode::TextNode(const std::string& text, const FontManager& fonts)
: mText()
{
  setString(text);
  mText.setFont(fonts.getResource(Fonts::Id::Main));
  mText.setCharacterSize(20);
}

TextNode::setString(const std::string& text)
{
  mText.setString(text);
  mText.setOrigin(mText.getLocalBounds().width / 2.f, mText.getLocalBounds().height / 2.f);
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(mText, states);
}

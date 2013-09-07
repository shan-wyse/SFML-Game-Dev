#include <SFML/Graphics/RenderTarget.hpp>
#include "SpriteNode.hpp"

SpriteNode::SpriteNode(const sf::Texture& texture)
: mSprite(texture)
{
  // empty
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect)
: mSprite(texture, textureRect)
{
  // empty
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(mSprite, states);
}
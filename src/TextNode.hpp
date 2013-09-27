#ifndef TEXT_NODE_CPP
#define TEXT_NODE_CPP

#include <SFML/Graphics/Text.hpp>
#include "SceneNode.hpp"
#include "ResourceIdentifiers.hpp"

class TextNode : public SceneNode
{
public:
  explicit          TextNode(const std::string& text, const FontManager& fonts);

  void              setString(const std::string& text);

private:
  virtual void      drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

  sf::Text          mText;
};

#endif // TEXT_NODE_CPP

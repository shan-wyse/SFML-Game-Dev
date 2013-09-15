#ifndef LABEL_HPP
#define LABEL_HPP

#include <SFML/Graphics/Text.hpp>
#include "Component.hpp"
#include "ResourceManager.hpp"
#include "ResourceIdentifiers.hpp"

namespace Gui
{

class Label : public Component
{
public:
  typedef std::shared_ptr<Label>    LabelPtr;

                                    Label(const std::string& text, const FontManager& fonts);

  virtual bool                      isSelectable() const;
  void                              setText(const std::string& text);

  virtual void                      processEvent(const sf::Event& event);

private:
  void                              draw(sf::RenderTarget& target, sf::RenderStates states) const;

  sf::Text                          mText;
};

}

#endif // LABEL_HPP

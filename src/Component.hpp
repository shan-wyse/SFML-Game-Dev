#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <memory>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namspace sf { class Event; }

namespace Gui
{

class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
  typedef std::shared_ptr<Component>      ComponentPtr;

                                          Component();
  virtual                                 ~Component();

  virtual bool                            isSelectable() const = 0;
  bool                                    isSelected() const;
  virtual void                            setSelected(bool selected);

  virtual bool                            isActive() const;
  virtual void                            setActive(bool active);

  virtual void                            processEvent(const sf::Event& event) = 0;

private:
  bool                                    mIsSelected;
  bool                                    mIsActive;
};

}

#endif // COMPONENT_HPP

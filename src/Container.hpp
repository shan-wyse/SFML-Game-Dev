#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <memory>
#include <vector>
#include "Component.hpp"

namespace Gui
{

class Container : public Component
{
public:
  typedef std::shared_ptr<Container>      ContainerPtr;

                                          Container();

  void                                    pack(Component::ComponentPtr component);

  virtual bool                            isSelectable() const;
  virtual void                            processEvent(const sf::Event& event);

private:
  virtual void                            draw(sf::RenderTarget& target, sf::RenderStates states) const;

  bool                                    hasSelection() const;
  void                                    setSelected(std::size_t index);
  void                                    selectPrevious();
  void                                    selectNext();

  std::vector<Component::ComponentPtr>    mChildren;
  int                                     mSelectedChild;
};

}

#endif // CONTAINER_HPP

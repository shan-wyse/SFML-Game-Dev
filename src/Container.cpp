#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Container.hpp"

namespace Gui
{

Container::Container()
: mChildren()
, mSelectedChild(-1)
{
  // empty
}

void Container::pack(Component::ComponentPtr component)
{
  mChildren.push_back(component);

  if (!hasSelection() && component->isSelectable())
    setSelected(mChildren.size() - 1);
}

bool Container::isSelectable() const
{
  return false;
}

void Container::processEvent(const sf::Event& event)
{
  if (hasSelection() && mChildren[mSelectedChild]->isActive())
    mChildren[mSelectedChild]->processEvent(event);

  else if (event.type == sf::Event::KeyReleased) {
    switch (event.key.code) {
      case sf::Keyboard::Escape:
        // requestStackPop();
        break;

      case sf::Keyboard::Return:
      case sf::Keyboard::Space:
        if (hasSelection())
          mChildren[mSelectedChild]->setActive(true);
        break;

      case sf::Keyboard::W:
      case sf::Keyboard::Up:
        selectPrevious();
        break;

      case sf::Keyboard::S:
      case sf::Keyboard::Down:
        selectNext();
        break;

      default:
        break;
    }
  }
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();

  for (const Component::ComponentPtr child : mChildren)
    target.draw(*child, states);
}

bool Container::hasSelection() const
{
  return mSelectedChild >= 0;
}

void Container::setSelected(std::size_t index)
{
  if (mChildren[index]->isSelectable()) {
    if (hasSelection())
      mChildren[mSelectedChild]->setSelected(false);

    mChildren[index]->setSelected(true);
    mSelectedChild = index;
  }
}

void Container::selectPrevious()
{
  if (!hasSelection())
    return;

  int prev = mSelectedChild;

  do
    prev = (prev + mChildren.size() - 1) % mChildren.size();
  while (!mChildren[prev]->isSelectable());

  setSelected(prev);
}

void Container::selectNext()
{
  if (!hasSelection())
    return;

  int next = mSelectedChild;

  do
    next = (next + 1) % mChildren.size();
  while (!mChildren[next]->isSelectable());

  setSelected(next);
}

}

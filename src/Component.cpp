#include "Component.hpp"

namespace Gui
{

Component::Component()
: mIsSelected(false)
, mIsActive(false)
{
  // empty
}

Component::~Component()
{
  // empty
}

bool Component::isSelected() const
{
  return mIsSelected;
}

void Component::setSelected(bool selected)
{
  mIsSelected = selected;
}

bool Component::isActive() const
{
  return mIsActive;
}

void Component::setActive(bool active)
{
  mIsActive = active;
}

}

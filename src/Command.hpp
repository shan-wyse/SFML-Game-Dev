#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <functional>
#include <cassert>
#include <SFML/System/Time.hpp>
#include "Category.hpp" // CHECK

class SceneNode;

struct Command
{
                                                Command();
  std::function<void(SceneNode&, sf::Time)>     action;

  unsigned int                                  category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function function)
{
  return [=] (SceneNode& node, sf::Time delta)
  {
    assert (dynamic_cast<GameObject*>(&node) != nullptr);
    function (static_cast<GameObject&>(node), delta);
  };
}

#endif // COMMAND_HPP

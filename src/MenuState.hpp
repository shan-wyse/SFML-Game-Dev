#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "State.hpp"

class MenuState : public State
{
public:
                            MenuState(StateStack& stack, Context context);

  virtual bool              processEvent(const sf::Event& event);
  virtual bool              update(sf::Time delta);
  virtual void              render();

  void                      updateOptionText();

private:
  enum class                MenuOptions { Play, Exit };

  sf::Sprite                mBackgroundSprite;

  std::vector<sf::Text>     mOptions;
  std::size_t               mOptionIndex;
};

#endif // MENU_STATE_HPP

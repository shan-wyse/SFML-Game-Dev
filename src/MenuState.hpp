#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "State.hpp"
#include "Container.hpp"

class MenuState : public State
{
public:
                            MenuState(StateStack& stack, Context context);

  virtual bool              processEvent(const sf::Event& event);
  virtual bool              update(sf::Time delta);
  virtual void              render();

private:
  sf::Sprite                mBackgroundSprite;
  Gui::Container            mGuiContainer;
};

#endif // MENU_STATE_HPP

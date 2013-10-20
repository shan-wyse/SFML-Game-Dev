#ifndef PAUSE_STATE_HPP
#define PAUSE_STATE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "State.hpp"
#include "Container.hpp"

class PauseState : public State
{
public:
                    PauseState(StateStack& stack, Context context, bool flag);
                    ~PauseState();

  virtual bool      processEvent(const sf::Event& event);
  virtual bool      update(sf::Time delta);
  virtual void      render();

private:
  sf::Sprite        mBackgroundSprite;
  sf::Text          mPausedText;
  Gui::Container    mGuiContainer;
};

#endif // PAUSE_STATE_HPP

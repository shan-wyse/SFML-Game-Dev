#ifndef PAUSE_STATE_HPP
#define PAUSE_STATE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "State.hpp"

class PauseState : public State
{
public:
                    PauseState(StateStack& stack, Context context);

  virtual bool      processEvent(const sf::Event& event);
  virtual bool      update(sf::Time delta);
  virtual void      render();

private:
  sf::Sprite        mBackgroundSprite;
  sf::Text          mPausedText;
  sf::Text          mInstructionText;
};

#endif // PAUSE_STATE_HPP

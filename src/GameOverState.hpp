#ifndef GAME_OVER_STATE_HPP
#define GAME_OVER_STATE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "State.hpp"
#include "Container.hpp"

class GameOverState : public State
{
public:
                    GameOverState(StateStack& stack, Context context);

  virtual bool      processEvent(const sf::Event& event);
  virtual bool      update(sf::Time delta);
  virtual void      render();

private:
  sf::Text          mGameOverText;
  sf::Time          mElapsedTime;
};

#endif // GAME_OVER_STATE_HPP

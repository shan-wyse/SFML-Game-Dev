#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <SFML/Graphics/Sprite.hpp> // CHECK
#include <SFML/Graphics/Text.hpp>
#include "State.hpp"
#include "World.hpp"
#include "Player.hpp"

class GameState : public State
{
public:
                    GameState(StateStack& stack, Context context);

  virtual bool      processEvent(const sf::Event& event);
  virtual bool      update(sf::Time delta);
  virtual void      render();

public:
  World             mWorld;
  Player&           mPlayer;
};

#endif // GAME_STATE_HPP

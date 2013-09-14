#include "GameState.hpp"

GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, mWorld(*context.window)
, mPlayer(*context.player)
{
  // empty
}

void GameState::processEvent(const sf::Event& event)
{
  CommandQueue& commands = mWorld.getCommandQueue();
  mPlayer.processEvent(event, commands);

  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    requestStackPush(States::Pause);

  return true;
}

void GameState::update(sf::Time delta)
{
  mWorld.update(delta);

  CommandQueue& commands = mWorld.getCommandQueue()
  mPlayer.handleRealtimeInput(commads);

  return true;
}

void GameState::render()
{
  mWorld.draw(); // CHANGE
}

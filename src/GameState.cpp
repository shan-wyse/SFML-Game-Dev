#include <SFML/Graphics/RenderWindow.hpp>
#include "GameState.hpp"
#include "MusicPlayer.hpp"

GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, mWorld(*context.window, *context.fonts)
, mPlayer(*context.player)
{
  mPlayer.setMissionStatus(Player::MissionInProgress);
  getContext().music->play(Music::MissionTheme);
}

bool GameState::processEvent(const sf::Event& event)
{
  CommandQueue& commands = mWorld.getCommandQueue();
  mPlayer.handleEvent(event, commands);

  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    requestStackPush(States::Pause);

  return true;
}

bool GameState::update(sf::Time delta)
{
  mWorld.update(delta);

  if (!mWorld.hasAlivePlayer()) {
    mPlayer.setMissionStatus(Player::MissionFailure);
    requestStackPush(States::GameOver);
  } else if (mWorld.hasPlayerReachedEnd()) {
    mPlayer.setMissionStatus(Player::MissionSuccess);
    requestStackPush(States::GameOver);
  }

  CommandQueue& commands = mWorld.getCommandQueue();
  mPlayer.handleRealtimeInput(commands);

  return true;
}

void GameState::render()
{
  mWorld.draw(); // CHANGE
}

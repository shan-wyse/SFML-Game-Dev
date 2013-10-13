#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "GameOverState.hpp"
#include "Player.hpp"
#include "ResourceManager.hpp"

GameOverState::GameOverState(StateStack& stack, Context context)
: State(stack, context)
, mGameOverText()
, mElapsedTime(sf::Time::Zero)
{
  mGameOverText.setFont(context.fonts->getResource(Fonts::Id::Main));

  if (context.player->getMissionStatus() == Player::MissionFailure)
    mGameOverText.setString("Mission failed!");
  else
    mGameOverText.setString("Mission successful!");

  mGameOverText.setCharacterSize(70);
  mGameOverText.setOrigin(mGameOverText.getLocalBounds().width / 2.f, mGameOverText.getLocalBounds().height / 2.f);
  mGameOverText.setPosition(0.5f * context.window->getSize().x, 0.4f * context.window->getSize().y);
}

bool GameOverState::processEvent(const sf::Event&)
{
  return false;
}

bool GameOverState::update(sf::Time delta)
{
  mElapsedTime += delta;

  if (mElapsedTime > sf::seconds(3)) {
    requestStateClear();
    requestStackPush(States::Menu);
  }

  return false;
}

void GameOverState::render()
{
  sf::RenderWindow& window = *getContext().window;
  window.setView(window.getDefaultView());

  sf::RectangleShape overlay;
  overlay.setFillColor(sf::Color(0, 0, 0, 150));
  overlay.setSize(window.getView().getSize());

  window.draw(overlay);
  window.draw(mGameOverText);
}

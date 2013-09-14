#include "PauseState.hpp"

void PauseState::processEvent(sf::Event& event)
{
  switch (event.key.code) {
    case sf::Keyboard::Escape:
      requestStatePop();
      break;
    case sf::Keyboard::Backspace:
      requestStateClear();
      requestStatePush(States::Menu);
      break;
  }

  return false;
}

void PauseState::update(sf::Time delta)
{
  return false;
}

void PauseState::render()
{
  sf::RenderWindow& window = *getContext().window;
  window.setView(window.getDefaultView());

  sf::RectangleShape overlay;
  overlay.setSize(sf::Vector2f(window.getSize()));
  overlay.setFillColor(sf::Color(0, 0, 0, 150));

  window.draw(overlay);
  window.draw(mPausedText);
  window.draw(mInstructionText);
}

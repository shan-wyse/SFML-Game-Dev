#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "PauseState.hpp"
#include "ResourceManager.hpp"

PauseState::PauseState(StateStack& stack, Context context)
: State(stack, context)
, mBackgroundSprite()
, mPausedText()
, mInstructionText()
{
  sf::Font& font = context.fonts->getResource(Fonts::Main);
  sf::Vector2f viewSize = context.window->getView().getSize();

  mPausedText.setFont(font);
  mPausedText.setString("Game Paused");
  mPausedText.setCharacterSize(70);
  mPausedText.setOrigin(mPausedText.getLocalBounds().width / 2.f, mPausedText.getLocalBounds().height / 2.f);
  mPausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

  mInstructionText.setFont(font);
  mInstructionText.setString("(Press Backspace to return to the main menu)");
  mInstructionText.setOrigin(mInstructionText.getLocalBounds().width / 2.f, mInstructionText.getLocalBounds().height / 2.f);
  mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

bool PauseState::processEvent(const sf::Event& event)
{
  switch (event.key.code) {
    case sf::Keyboard::Escape:
      requestStackPop();
      break;
    case sf::Keyboard::BackSpace:
      requestStackClear();
      requestStackPush(States::Menu);
      break;
  }

  return false;
}

bool PauseState::update(sf::Time delta)
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

#include "MenuState.hpp"

MenuState::MenuState(StateStack& stack, Context context)
{
  sf::Text playOption;
  playOption.setFont(font);
  playOption.setString("Play");
  centerOrigin(playOption);
  playOption.setPosition(context.window->getView().getSize() / 2.f);
  mOptions.push_back(playOption);
}

void MenuState::processEvent(sf::Event& event)
{
  if (event.key.code == sf::Keyboard::W) { // SWITCH
    if (mOptionIndex > 0) // TERNARY
      mOptionIndex--;
    else
      mOptionIndex = mOptions.size() - 1;

    updateOptionText();
  } else if (event.key.code == sf::Keyboard::S) {
    if (mOptionIndex < mOptions.size() - 1)
      mOptionIndex++;
    else
      mOptionIndex = 0;

    updateOptionText();
  } else if (event.key.code == sf::Keyboard::Return) {
    if (mOptionIndex == Play) { // REFACTOR
      requestStackPop();
      requestStackPush(States::Game);
    } else if (mOptionIndex == Exit)
      requestStackPop();
  }
}

void MenuState::updateOptionText()
{
  if (mOptions.empty())
    return;

  for (sf::Text& text : mOptions)
    text.setColor(sf::Color::White);

  mOptions[mOptionIndex].setColor(sf::Color::Red);
}

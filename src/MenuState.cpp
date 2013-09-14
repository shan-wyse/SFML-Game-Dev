#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include "MenuState.hpp"
#include "ResourceManager.hpp"

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, mOptions()
, mOptionIndex(0)
{
  sf::Texture& texture = context.textures->getResource(Textures::Id::TitleScreen);
  sf::Font& font = context.fonts->getResource(Fonts::Main);

  mBackgroundSprite.setTexture(texture);

  sf::Text playOption;
  playOption.setFont(font);
  playOption.setString("Play");
  playOption.setOrigin(playOption.getLocalBounds().width / 2.f, playOption.getLocalBounds().height / 2.f);
  playOption.setPosition(context.window->getView().getSize() / 2.f);
  mOptions.push_back(playOption);

  sf::Text exitOption;
  exitOption.setFont(font);
  exitOption.setString("Exit");
  exitOption.setOrigin(exitOption.getLocalBounds().width / 2.f, exitOption.getLocalBounds().height / 2.f);
  exitOption.setPosition(exitOption.getPosition() + sf::Vector2f(0.f, 30.f));
  mOptions.push_back(exitOption);

  updateOptionText();
}

bool MenuState::processEvent(const sf::Event& event)
{
  if (event.type != sf::Event::KeyPressed)
    return false;

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
    if (true) {//mOptions[mOptionIndex] == "Play") { // REFACTOR
      requestStackPop();
      requestStackPush(States::Game);
    } else if (false) //mOptions[mOptionIndex] == "Exit")
      requestStackPop();
  }

  return true;
}

bool MenuState::update(sf::Time delta)
{
  return true;
}

void MenuState::render()
{
  sf::RenderWindow& window = *getContext().window;

  window.setView(window.getDefaultView());
  window.draw(mBackgroundSprite);

  for (const sf::Text& text : mOptions)
    window.draw(text);
}

void MenuState::updateOptionText()
{
  if (mOptions.empty())
    return;

  for (sf::Text& text : mOptions)
    text.setColor(sf::Color::White);

  mOptions[mOptionIndex].setColor(sf::Color::Red);
}

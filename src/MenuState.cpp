#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include "MenuState.hpp"
#include "ResourceManager.hpp"

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, mGuiContainer()
{
  sf::Texture& texture = context.textures->getResource(Textures::Id::TitleScreen);
  sf::Font& font = context.fonts->getResource(Fonts::Id::Main);

  mBackgroundSprite.setTexture(texture);

  // sf::Text playOption;
  // playOption.setFont(font);
  // playOption.setString("Play");
  // playOption.setOrigin(playOption.getLocalBounds().width / 2.f, playOption.getLocalBounds().height / 2.f);
  // playOption.setPosition(context.window->getView().getSize() / 2.f);
  // mOptions.push_back(playOption);

  sf::Text exitOption;
  exitOption.setFont(font);
  exitOption.setString("Exit");
  exitOption.setOrigin(exitOption.getLocalBounds().width / 2.f, exitOption.getLocalBounds().height / 2.f);
  exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
  mOptions.push_back(exitOption);

  updateOptionText();

  auto playButton = std::make_shared<Gui::Button> (*context.textures, *context.fonts);
  playButton->setPosition(100, 250);
  playButton->setText("Play");
  playButton->setCallback([this] ()
  {
    requestStackPop();
    requestStackPush(States::Game);
  });

  mGuiContainer.pack(playButton);
}

bool MenuState::processEvent(const sf::Event& event)
{
  mGuiContainer.processEvent(event);
  return false;
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
  window.draw(mGuiContainer);
}

void MenuState::updateOptionText()
{
  if (mOptions.empty())
    return;

  for (sf::Text& text : mOptions)
    text.setColor(sf::Color::White);

  mOptions[mOptionIndex].setColor(sf::Color::Red);
}

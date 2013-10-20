#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include "MenuState.hpp"
#include "ResourceManager.hpp"
#include "MusicPlayer.hpp"
#include "Button.hpp"

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, mGuiContainer()
{
  getContext().musicPlayer->play(Music::MenuTheme);
  sf::Texture& texture = context.textures->getResource(Textures::Id::TitleScreen);
  mBackgroundSprite.setTexture(texture);

  auto playButton = std::make_shared<Gui::Button> (context);
  playButton->setPosition(100, 250);
  playButton->setText("Play");
  playButton->setCallback([this] ()
  {
    requestStackPop();
    requestStackPush(States::Loading);
  } );

  auto hostPlayButton = std::make_shared<Gui::Button> (context);
  hostPlayButton->setPosition(100, 300);
  hostPlayButton->setText("Host");
  hostPlayButton->setCallback([this] ()
  {
    requestStackPop();
    requestStackPush(States::HostGame);
  } );

  auto joinPlayButton = std::make_shared<Gui::Button> (context);
  joinPlayButton->setPosition(100, 350);
  joinPlayButton->setText("Join");
  joinPlayButton->setCallback([this] ()
  {
    requestStackPop();
    requestStackPush(States::JoinGame);
  } );

  auto settingsButton = std::make_shared<Gui::Button> (context);
  settingsButton->setPosition(100, 400);
  settingsButton->setText("Settings");
  settingsButton->setCallback([this] ()
  {
    requestStackPush(States::Settings);
  } );

  auto exitButton = std::make_shared<Gui::Button> (context);
  exitButton->setPosition(100, 450);
  exitButton->setText("Exit");
  exitButton->setCallback([this] ()
  {
    requestStackPop();
  } );

  mGuiContainer.pack(playButton);
  mGuiContainer.pack(hostPlayButton);
  mGuiContainer.pack(joinPlayButton);
  mGuiContainer.pack(settingsButton);
  mGuiContainer.pack(exitButton);
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

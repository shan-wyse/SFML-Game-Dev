#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "PauseState.hpp"
#include "ResourceManager.hpp"
#include "MusicPlayer.hpp"
#include "Button.hpp"

PauseState::PauseState(StateStack& stack, Context context)
: State(stack, context)
, mBackgroundSprite()
, mPausedText()
, mGuiContainer()
{
  getContext().music->setPaused(true);
  sf::Font& font = context.fonts->getResource(Fonts::Id::Main);
  sf::Vector2f windowSize(context.window->getSize());

  mPausedText.setFont(font);
  mPausedText.setString("Game Paused");
  mPausedText.setCharacterSize(70);
  mPausedText.setOrigin(mPausedText.getLocalBounds().width / 2.f, mPausedText.getLocalBounds().height / 2.f);
  mPausedText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

  auto returnButton = std::make_shared<Gui::Button> (*context.textures, *context.fonts);
  returnButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 75);
  returnButton->setText("Return");
  returnButton->setCallback([this] () { requestStackPop(); });

  auto backToMenuButton = std::make_shared<Gui::Button> (*context.textures, *context.fonts);
  backToMenuButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 125);
  backToMenuButton->setText("Back to Menu");
  backToMenuButton->setCallback([this] () { requestStateClear(); requestStackPush(States::Menu); });

  mGuiContainer.pack(returnButton);
  mGuiContainer.pack(backToMenuButton);
}

PauseState::~PauseState()
{
  getContext().music->setPaused(false);
}

bool PauseState::processEvent(const sf::Event& event)
{
  mGuiContainer.processEvent(event);
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
  window.draw(mGuiContainer);
}

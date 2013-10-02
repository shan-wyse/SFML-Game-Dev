#include <SFML/Graphics/RenderWindow.hpp>
#include "SettingsState.hpp"
#include "ResourceManager.hpp"
#include "StringHelper.hpp"

SettingsState::SettingsState(StateStack& stack, Context context)
: State(stack, context)
, mGuiContainer()
{
  mBackgroundSprite.setTexture(context.textures->getResource(Textures::Id::TitleScreen));

  addButtonLabel(Player::MoveUp,        300.f, "Move Up",     context);
  addButtonLabel(Player::MoveDown,      350.f, "Move Down",   context);
  addButtonLabel(Player::MoveLeft,      400.f, "Move Left",   context);
  addButtonLabel(Player::MoveRight,     450.f, "Move Right",  context);
  addButtonLabel(Player::Fire,          500.f, "Fire",        context);
  addButtonLabel(Player::LaunchMissile, 550.f, "Missile",     context);

  auto backButton = std::make_shared<Gui::Button>(context);
  backButton->setPosition(80.f, 620.f);
  backButton->setText("Back");
  backButton->setCallback(std::bind(&SettingsState::requestStackPop, this));

  mGuiContainer.pack(backButton);
  updateLabels();
}

bool SettingsState::processEvent(const sf::Event& event)
{
  bool isKeyBinding = false;

  for (std::size_t action = 0; action < Player::Count; ++action) {
    if (mBindingButtons[action]->isActive()) {
      isKeyBinding = true;

      if (event.type == sf::Event::KeyReleased) {
        getContext().player->setAssignedKey(static_cast<Player::Action>(action), event.key.code);
        mBindingButtons[action]->setActive(false);
      }

      break;
    }
  }

  if (isKeyBinding)
    updateLabels();
  else
    mGuiContainer.processEvent(event);

  return false;
}

bool SettingsState::update(sf::Time delta)
{
  return true;
}

void SettingsState::render()
{
  sf::RenderWindow& window = *getContext().window;

  window.draw(mBackgroundSprite);
  window.draw(mGuiContainer);
}

void SettingsState::updateLabels()
{
  Player& player = *getContext().player;

  for (std::size_t i = 0; i < Player::Count; ++i) {
    sf::Keyboard::Key key = player.getAssignedKey(static_cast<Player::Action>(i));
    mBindingLabels[i]->setText(toString(key));
  }
}

void SettingsState::addButtonLabel(Player::Action action, float yPos, const std::string& text, Context context)
{
  mBindingButtons[action] = std::make_shared<Gui::Button> (context);
  mBindingButtons[action]->setPosition(80.f, yPos);
  mBindingButtons[action]->setText(text);
  mBindingButtons[action]->setToggle(true);

  mBindingLabels[action] = std::make_shared<Gui::Label> ("", *context.fonts);
  mBindingLabels[action]->setPosition(300.f, yPos + 15.f);

  mGuiContainer.pack(mBindingButtons[action]);
  mGuiContainer.pack(mBindingLabels[action]);
}

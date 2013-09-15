#include <SFML/Graphics/RenderWindow.hpp>
#include "SettingsState.hpp"
#include "ResourceManager.hpp"

SettingsState::SettingsState(StateStack& stack, Context context)
: State(stack, context)
, mGuiContainer()
{
  mBackgroundSprite.setTexture(context.textures->getResource(Texrures::TitleScreen));

  addButtonLabel(Player::Action::MoveUp,    150.f, "MoveUp",    context);
  addButtonLabel(Player::Action::MoveDown,  200.f, "MoveDown",  context);
  addButtonLabel(Player::Action::MoveLeft,  250.f, "MoveLeft",  context);
  addButtonLabel(Player::Action::MoveRight, 300.f, "MoveRight", context);

  updateLabels();


  // // possible typedef
  // mBindingButtons[Player::Action::MoveUp] = std::make_shared<Gui::Button>();
  // mBindingButtons[Player::Action::MoveDown] = std::make_shared<Gui::Button>();
  // mBindingButtons[Player::Action::MoveLeft] = std::make_shared<Gui::Button>();
  // mBindingButtons[Player::Action::MoveRight] = std::make_shared<Gui::Button>();

  // mBindingLabels[Player::Action::MoveUp] = std::make_shared<Gui::Label>();
  // mBindingLabels[Player::Action::MoveDown] = std::make_shared<Gui::Label>();
  // mBindingLabels[Player::Action::MoveLeft] = std::make_shared<Gui::Label>();
  // mBindingLabels[Player::Action::MoveRight] = std::make_shared<Gui::Label>();

  // updateLabels();

  auto backButton = std::make_shared<Gui::Button>();
  backButton->setPosition(100, 375);
  backButton->setText("Back");
  backButton->setCallback([this] () { requestStackPop(); });

  // mGuiContainer.pack(mBindingButtons[Player::Action::MoveUp]);
  // mGuiContainer.pack(mBindingButtons[Player::Action::MoveDown]);
  // mGuiContainer.pack(mBindingButtons[Player::Action::MoveLeft]);
  // mGuiContainer.pack(mBindingButtons[Player::Action::MoveRight]);

  // mGuiContainer.pack(mBindingLabels[Player::Action::MoveUp]);
  // mGuiContainer.pack(mBindingLabels[Player::Action::MoveDown]);
  // mGuiContainer.pack(mBindingLabels[Player::Action::MoveLeft]);
  // mGuiContainer.pack(mBindingLabels[Player::Action::MoveRight]);

  mGuiContainer.pack(backButton);
}

bool SettingsState::processEvent(const sf::Event& event)
{
  bool isKeyBinding = false;

  for (std::size_t action = 0; action < Player::Action::ActionCount; ++action) {
    if (mBindingButtons[action]->isActive()) {
      isKeyBinding = true;

      if (event.type == sf::Event::KeyReleased) {
        getContext().player->setAssignedKey(static_cast<Player::Action>(action), event.key.code);
        mBindingButtons[action]->deactive();
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
  // empty
}

void SettingsState::render()
{
  sf::RenderWindow window = *getContext().window;

  window.draw(mBackgroundSprite);
  window.draw(mGuiContainer);
}

void SettingsState::updateLabels()
{
  Player& player = *getContext().player;

  for (std::size_t i = 0; i < Player::Action::ActionCount; ++i) {
    sf::Keyboard::Key key = player.getAssignedKey(static_cast<Player::Action>(i));
    mBindingLabels[i]->setText(toString(key));
  }
}

void SettingsState::addButtonLabel(Player::Action action, float yPos, const std::string& text, Context context)
{
  mBindingButtons[action] = std::make_shared<Gui::Button> (*context.fonts, *context.textures);
  mBindingButtons[action]->setPosition(80.f, yPos);
  mBindingButtons[action]->setText(text);
  mBindingButtons[action]->setToggle(true);

  mBindingLabels[action] = std::make_shared<Gui::Labels> ("", *context.fonts);
  mBindingLabels[action]->setPosition(300.f, y + 15.f);

  mGuiContainer.pack(mBindingButtons[action]);
  mGuiContainer.pack(mBindingLabels[action]);
}

#ifndef SETTINGS_STATE_HPP
#define SETTINGS_STATE_HPP

#include <array>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "State.hpp"
#include "Player.hpp"
#include "Container.hpp"
#include "Button.hpp"
#include "Label.hpp"

class SettingsState : public State
{
public:
                      SettingsState(StateStack& stack, Context context);

  virtual bool        processEvent(const sf::Event& event);
  virtual bool        update(sf::Time delta);
  virtual void        render();

  private:
    void              updateLabels();
    void              addButtonLabel(Player::Action action, float yPos, const std::string& text, Context context);

    sf::Sprite        mBackgroundSprite;
    Gui::Container    mGuiContainer;

    std::array<Gui::Button::ButtonPtr, Player::ActionCount>     mBindingButtons;
    std::array<Gui::Label::LabelPtr, Player::ActionCount>       mBindingLabels;
};

#endif // SETTINGS_STATE_HPP

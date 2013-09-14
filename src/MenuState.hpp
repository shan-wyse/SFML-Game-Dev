#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

class MenuState : public State
{
public:
                            MenuState(StateStack& stack, Context context);

  virtual bool              processEvent(const sf::Event& event);
  virtual bool              update(sf::Time delta);
  virtual void              render();

private:
  enum class                MenuOptions { Play, Exit };

  sf::Sprite                mBackgroundSprite;
  sf::Text                  mText;

  std::vector<sf::Text>     mOptions;
  std::size_t               mOptionIndex;
};

#endif // MENU_STATE_HPP

#ifndef TITLE_STATE_HPP
#define TITLE_STATE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "State.hpp"

class TitleState : public State
{
public:
                    TitleState(StateStack& stack, Context context);

  virtual bool      processEvent(const sf::Event& event);
  virtual bool      update(sf::Time delta);
  virtual void      render();

private:
  sf::Sprite        mBackgroundSprite;
  sf::Text          mText;

  bool              mShowText;
  sf::Time          mTextEffectTime;
};

#endif // TITLE_STATE_HPP

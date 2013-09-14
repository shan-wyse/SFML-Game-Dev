#ifndef PAUSE_STATE_HPP
#define PAUSE_STATE_HPP

clase PauseState : public State
{
public:
                    PauseState(StateStack& stack, Context context);

  virtual bool      processEvent(const sf::Event& event);
  virtual bool      update(sf::Time delta);
  virtual void      render();

private:
  sf::Sprite        mBackgroundSprite;
  sf::Text          mText;

  bool              mShowText;
  sf::Time          mTextEffectTime;
};

#endif // PAUSE_STATE_HPP

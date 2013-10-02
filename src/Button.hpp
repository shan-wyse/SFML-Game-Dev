#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <memory>
#include <functional>
#include <string>
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Component.hpp"
#include "State.hpp"
#include "ResourceIdentifiers.hpp"

namespace Gui
{

class Button : public Component
{
public:
  typedef std::shared_ptr<Button>     ButtonPtr;
  typedef std::function<void()>       Callback;

  enum                                Type { Deselected, Selected, Pressed, Count };

                                      Button(State::Context context);

  virtual bool                        isSelectable() const;
  virtual void                        setSelected(bool selected);
  virtual void                        setActive(bool active);

  virtual void                        processEvent(const sf::Event& event);

  void                                setCallback(Callback callback);
  void                                setText(const std::string& text);
  void                                setToggle(bool toggle);

private:
  virtual void                        draw(sf::RenderTarget& target, sf::RenderStates states) const;
  void                                changeTexture(Type buttonType);

  Callback                            mCallback;
  // const sf::Texture&                  mDeselectedTexture;
  // const sf::Texture&                  mSelectedTexture;
  // const sf::Texture&                  mPressedTexture;
  sf::Sprite                          mSprite;
  sf::Text                            mText;
  SoundPlayer&                        mSoundPlayer;
  bool                                mIsToggle;
};

}

#endif // BUTTON_HPP

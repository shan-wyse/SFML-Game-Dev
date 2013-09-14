#ifndef STATE_HPP
#define STATE_HPP

#include <memory>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"

namespace sf { class RenderWindow; } // CHECK
class StateStack;
class Player;

class State
{
public:
  typedef std::unique_ptr<State>      StatePtr;

  struct Context
  {
                                      Context(sf::RenderWindow& window, TextureManager& textures,
                                              FontManager& fonts, Player& player);

    sf::RenderWindow*                 window;
    TextureManager*                   textures;
    FontManager*                      fonts;
    Player*                           player;
  };

                                      State(StateStack& stack, Context context);
  virtual                             ~State();

  virtual bool                        processEvent(const sf::Event& event) = 0;
  virtual bool                        update(sf::Time delta) = 0;
  virtual void                        render() = 0;

protected:
  void                                requestStackPush(States::Id stateId);
  void                                requestStackPop();
  void                                requestStackClear();

  Context                             getContext() const;

private:
  StateStack*                         mStack;
  Context                             mContext;
};

#endif // STATE_HPP

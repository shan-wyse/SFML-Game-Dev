#ifndef STATE_STACK_HPP
#define STATE_STACK_HPP

#include <vector>
#include <map>
#include <functional>
#include <vector>
#include <functional>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"

namespace sf { class Event; class RenderWindow; }

class StateStack : private sf::NonCopyable
{
public:
  enum class                                                Action { Push, Pop, Clear };

  explicit                                                  StateStack(State::Context context);

  template <typename type>
  void                                                      registerState(States::Id stateId);
  template <typename type, typename Param1>
  void                                                      registerState(States::Id stateId, Param1 arg1);

  void                                                      processEvent(const sf::Event& event);
  void                                                      update(sf::Time delta);
  void                                                      render();

  void                                                      pushState(States::Id stateId);
  void                                                      popState();
  void                                                      clearStates();

  bool                                                      isEmpty() const;

private:
  struct PendingChange
  {
    explicit                                                PendingChange(Action action,
                                                                States::Id stateId = States::None);

    Action                                                  action;
    States::Id                                              stateId;
  };

  State::StatePtr                                           createState(States::Id stateId);
  void                                                      applyPendingChanges();

  std::vector<State::StatePtr>                              mStack;
  std::vector<PendingChange>                                mPendingList;

  State::Context                                            mContext;
  std::map< States::Id, std::function<State::StatePtr()> >  mFactories;
};

template <typename type> // SINGLE VARIADIC?
void StateStack::registerState(States::Id stateId)
{
  mFactories[stateId] = [this] ()
  {
    return State::StatePtr(new type(*this, mContext));
  };
}

template <typename type, typename Param1>
void StateStack::registerState(States::Id stateId, Param1 arg1)
{
  mFactories[stateId] = [this, arg1] ()
  {
    return State::StatePtr(new type(*this, mContext, arg1));
  };
}

#endif // STATE_STACK_HPP

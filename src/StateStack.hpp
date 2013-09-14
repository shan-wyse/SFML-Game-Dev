#ifndef STATE_STACK_HPP
#define STATE_STACK_HPP

#include <vector>
#include <map>
#include <functional>
#include <vector>
#include <map>
#include <functional>
#include <SFML/System/NonCopyable.hpp>
#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "ResourceIdentifiers.hpp"

class StateStack : private sf::NonCopyable
{
public:
  enum class                                                Action { Push, Pop, Clear };

  explicit                                                  StateStack(State::Context context);

  template <typename type>
  void                                                      registerState(States::Id stateId);

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

#endif // STATE_STACK_HPP

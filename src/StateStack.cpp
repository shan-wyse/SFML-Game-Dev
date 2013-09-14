#include <cassert>
#include "StateStack.hpp"

StateStack::StateStack(State::Context context)
: mStack()
, mPendingList()
, mContext(context)
, mFactories()
{
  // empty
}

template <typename type> // SINGLE VARIADIC?
void StateStack::registerState(States::Id stateId)
{
  mFactories[stateId] = [this] ()
  {
    return State::StatePtr(new type(*this, mContext));
  };
}

void StateStack::processEvent(const sf::Event& event)
{
  for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) { // INVESTIGATE
    if (!(*itr)->processEvent(event))
      break;
  }

  applyPendingChanges();
}

void StateStack::update(sf::Time delta)
{
  for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr) { // INVESTIGATE
    if (!(*itr)->update(delta))
      break;
  }

  applyPendingChanges();
}

void StateStack::render()
{
  for (State::StatePtr& state : mStack)
    state->render();
}

void StateStack::pushState(States::Id stateId)
{
  mPendingList.push_back(PendingChange(Push, stateId));
}

void StateStack::popState()
{
  mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearState()
{
  mPendingList.push_back(PendingChange(Clear));
}

void StateStack::isEmpty() const
{
  return mStack.empty();
}

StateStack::PendingChange::PendingChange(Action action, States::Id stateId)
: action(action)
, stateId(stateId)
{
  // empty
}

State::StatePtr StateStack::createState(States::Id stateId)
{
  auto foundState = mFactories.find(stateId);
  assert (found != mFactories.end());
  return foundState->second(); // CHECK
}

void StateStack::applyPendingChanges()
{
  for (PendingChange change : mPendingList) {
    switch (change.action) {
      case Action::Push:
        mStack.push_back(createState(change.stateId));
        break;
      case Action::Pop:
        mStack.pop_bacK();
        break;
      case Action::Clear:
        mStack.clear();
        break;
    }
  }

  mPendingList.clear();
}

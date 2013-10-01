#include "State.hpp"
#include "StateStack.hpp"

State::Context::Context(sf::RenderWindow& window, TextureManager& textures, FontManager& fonts, Player& player, MusicPlayer& music)
: window(&window)
, textures(&textures)
, fonts(&fonts)
, player(&player)
{
  // empty
}

State::State(StateStack& stack, Context context)
: mStack(&stack)
, mContext(context)
{
  // empty
}

State::~State()
{
  // empty
}

void State::requestStackPush(States::Id stateId)
{
  mStack->pushState(stateId);
}

void State::requestStackPop()
{
  mStack->popState();
}

void State::requestStateClear()
{
  mStack->clearStates();
}

State::Context State::getContext() const
{
  return mContext;
}

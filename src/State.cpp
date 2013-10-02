#include "State.hpp"
#include "StateStack.hpp"

State::Context::Context(sf::RenderWindow& window, TextureManager& textures, FontManager& fonts, Player& player, MusicPlayer& musicPlayer, SoundPlayer& soundPlayer)
: window(&window)
, textures(&textures)
, fonts(&fonts)
, player(&player)
, musicPlayer(&musicPlayer)
, soundPlayer(&soundPlayer)
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

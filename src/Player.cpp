#include <map>
#include <string>
#include <algorithm>
// #include <SFML/Window/Event.hpp>
#include "Player.hpp"
#include "Aircraft.hpp"
#include "CommandQueue.hpp"

struct AircraftMover
{
  AircraftMover(float xVel, float yVel)
  : velocity(xVel, yVel)
  {
    // empty
  }

  void operator() (Aircraft& aircraft, sf::Time) const
  {
    aircraft.accelerate(velocity * aircraft.getMaxSpeed());
  }

  sf::Vector2f velocity;
};

Player::Player()
: mCurrentMissionStatus(MissionInProgress)
{
  mKeyBinding[sf::Keyboard::W]      = MoveUp;
  mKeyBinding[sf::Keyboard::S]      = MoveDown;
  mKeyBinding[sf::Keyboard::A]      = MoveLeft;
  mKeyBinding[sf::Keyboard::D]      = MoveRight;
  mKeyBinding[sf::Keyboard::Space]  = Fire;
  mKeyBinding[sf::Keyboard::E]      = LaunchMissile;

  initializeActions();

  for (auto& pair : mActionBinding)
    pair.second.category = Category::PlayerAircraft;
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
  for (auto pair : mKeyBinding) {
    if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
      commands.push(mActionBinding[pair.second]);
  }
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
  if (event.type == sf::Event::KeyPressed) {
    auto foundBinding = mKeyBinding.find(event.key.code);
    if (foundBinding != mKeyBinding.end() && !isRealtimeAction(foundBinding->second))
      commands.push(mActionBinding[foundBinding->second]);
  }
}

void Player::setAssignedKey(Action action, sf::Keyboard::Key key)
{
  /*for (auto binding : mKeyBinding) {
    if (binding.second == action)
      mKeyBinding.erase(&binding);
  }*/

  for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
  {
    if (itr->second == action)
      mKeyBinding.erase(itr++);
    else
      ++itr;
  }
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
  for (auto pair : mKeyBinding) {
    if (pair.second == action)
      return pair.first;
  }

  return sf::Keyboard::Unknown;
}

void Player::setMissionStatus(MissionStatus status) { mCurrentMissionStatus = status; }

Player::MissionStatus Player::getMissionStatus() const { return mCurrentMissionStatus; }

void Player::initializeActions()
{
  // const float playerSpeed = 200.f;

  mActionBinding[MoveUp].action           = derivedAction<Aircraft>(AircraftMover( 0, -1));
  mActionBinding[MoveDown].action         = derivedAction<Aircraft>(AircraftMover( 0, +1));
  mActionBinding[MoveLeft].action         = derivedAction<Aircraft>(AircraftMover(-1,  0));
  mActionBinding[MoveRight].action        = derivedAction<Aircraft>(AircraftMover(+1,  0));

  mActionBinding[Fire].action             = derivedAction<Aircraft>([] (Aircraft& a, sf::Time) { a.fire(); } );
  mActionBinding[LaunchMissile].action    = derivedAction<Aircraft>([] (Aircraft& a, sf::Time) { a.launchMissile(); } );
}

bool Player::isRealtimeAction(Action action)
{
  switch (action) {
    case MoveUp:
    case MoveDown:
    case MoveLeft:
    case MoveRight:
    case Fire:
      return true;
    default:
      return false;
  }
}

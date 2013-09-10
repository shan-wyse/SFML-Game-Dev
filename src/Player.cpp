#include <map>
#include <string>
#include <algorithm>
#include <SFML/Window/Event.hpp>
#include "Player.hpp"
#include "Aircraft.hpp"

struct AircraftMover
{
  AircraftMover(float xVel, float yVel)
  : velocity(xVel, yVel)
  {
    // empty
  }

  void operator() (Aircraft& aircraft, sf::Time) const
  {
    aircraft.accelerate(velocity);
  }

  sf::Vector2f velocity;
};

Player::Player()
{
  mKeyBinding[sf::Keyboard::Up] = Action::MoveUp;
  mKeyBinding[sf::Keyboard::Down] = Action::MoveDown;
  mKeyBinding[sf::Keyboard::Left] = Action::MoveLeft;
  mKeyBinding[sf::Keyboard::Right] = Action::MoveRight;
  // investigate
  mKeyBinding[sf::Keyboard::Escape] = Action::Close;

  initializeActions();

  /*mActionBinding[Action::MoveLeft].action = [] (SceneNode& node, sf::Time delta)
  {
    node.move(-playerSpeed * delta.asSeconds(), 0.f);
  };

  mActionBinding[Action::MoveRight].action = [] (SceneNode& node, sf::Time delta)
  {
    node.move(playerSpeed * delta.asSeconds(), 0.f);
  };*/

  for (auto& pair : mActionBinding)
    pair.second.category = Category::PlayerAircraft;
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
  for (auto pair : mKeyBinding) {
    if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
      commands.push(mActionBinding[pair.second]);
  }

  /*const float playerSpeed = 30.f;

  /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    Command moveLeft;
    moveLeft.category = Category::PlayerAircraft;
    moveLeft.action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
    commands.push(moveLeft);
  }*/
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
  if (event.type == sf::Event::KeyPressed) {
    auto foundBinding = mKeyBinding.find(event.key.code);
    if (foundBinding != mKeyBinding.end() && !isRealtimeAction(foundBinding->second))
      commands.push(mActionBinding[foundBinding->second]);
  }
  /*if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
    Command output;
    output.category = Category::PlayerAircraft;

    output.action = [ ] (SceneNode& node, sf::Time)
    {
      std::cout << node.getPosition().x << "," << node.getPosition().y << std::endl;
    };

    commands.push(output);
  }*/
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

void Player::initializeActions()
{
  const float playerSpeed = 200.f;

  mActionBinding[Action::MoveUp].action     = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
  mActionBinding[Action::MoveDown].action   = derivedAction<Aircraft>(AircraftMover(0.f, +playerSpeed));
  mActionBinding[Action::MoveLeft].action   = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
  mActionBinding[Action::MoveRight].action  = derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f));
}

bool Player::isRealtimeAction(Action action)
{
  switch (action) {
    case Action::MoveUp:
    case Action::MoveDown:
    case Action::MoveLeft:
    case Action::MoveRight:
      return true;
    default:
      return false;
  }
}

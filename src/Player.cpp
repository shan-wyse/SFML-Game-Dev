#include <SFML/Window/Event.hpp>
#include "Player.hpp"
#include "Aircraft.hpp"
#include "Category.hpp"
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
    aircraft.setVelocity(aircraft.getVelocity() + velocity); //accelerate(velocity);
  }

  sf::Vector2f velocity;
};

void Player::handleRealtimeInput(CommandQueue& commands)
{
  const float playerSpeed = 30.f;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    Command moveLeft;
    moveLeft.category = Category::PlayerAircraft;
    moveLeft.action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
    commands.push(moveLeft);
  }
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
    command output;
    output.category = Category::PlayerAircraft;

    output.action = [ ] (SceneNode& node, sf::Time)
    {
      std::cout << node.getPosition().x << "," << node.getPosition().y << std::endl;
    }

    commands.push(output);
  }
}

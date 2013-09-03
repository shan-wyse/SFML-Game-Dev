#include "Game.hpp"
#include <iostream> // DEBUG ONLY

Game::Game()
: mWindow(sf::VideoMode(640, 480), "SFML Application")
, mTexture()
, mPlayer()
, mIsMovingUp(false) // possibly remove?
, mIsMovingDown(false)
, mIsMovingLeft(false)
, mIsMovingRight(false)
{
  if (!mTexture.loadFromFile("media/textures/player.png"))
  {
    // log error
  }

  // mPlayer.setTexture(mTexture);
  // mPlayer.setPosition(100.f, 100.f);

  mTextures.loadTexture(Textures::ID::Landscape, "media/textures/landscape.png");
  mTextures.loadTexture(Textures::ID::Airplane, "media/textures/player.png");
  mTextures.loadTexture(Textures::ID::Missile, "media/texturs/missile.png");

  mPlayer.setTexture(mTextures.getTexture(Textures::ID::Airplane));
  mPlayer.setPosition(100.f, 100.f);
}

void Game::run()
{
  sf::Clock               clock;
  sf::Time                elapsedTime = sf::Time::Zero;
  const static sf::Time   FRAME_DURATION = sf::seconds(1.f / 60.f); // CHANGE TO CONFIG FILE

  while (mWindow.isOpen())
  {
    // sf::Time  deltaTime = clock.restart();
    elapsedTime += clock.restart();
    while (elapsedTime > FRAME_DURATION)
    {
      std::cout << "Time/frame: " << elapsedTime.asMilliseconds() << "ms" << std::endl; // DEBUG ONLY
      std::cout << "FPS: " << (1 / elapsedTime.asSeconds()) << std::endl; // DEBUG ONLY
      system("cls"); // DEBUG ONLY
      elapsedTime -= FRAME_DURATION;
      processEvents();
      update(FRAME_DURATION);

    }
    render();
  }
}

void Game::processEvents()
{
  sf::Event event;
  while (mWindow.pollEvent(event))
  {
    switch (event.type)
    {
      case sf::Event::KeyPressed:
        handlePlayerInput(event.key.code, true);
        break;
      case sf::Event::KeyReleased:
        handlePlayerInput(event.key.code, false);
        break;
      case sf::Event::Closed:
        mWindow.close();
        break;
    }
  }
}

void Game::update(sf::Time deltaTime)
{
  sf::Vector2f movement(0.f, 0.f);

  if (mIsMovingUp)      movement.y -= 1.f;
  if (mIsMovingDown)    movement.y += 1.f;
  if (mIsMovingLeft)    movement.x -= 1.f;
  if (mIsMovingRight)   movement.x += 1.f;

  mPlayer.move(movement * deltaTime.asSeconds());
}

void Game::render()
{
  mWindow.clear();
  mWindow.draw(mPlayer);
  mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
  switch (key)
  {
    case sf::Keyboard::W: mIsMovingUp       = isPressed; break;
    case sf::Keyboard::S: mIsMovingDown     = isPressed; break;
    case sf::Keyboard::A: mIsMovingLeft     = isPressed; break;
    case sf::Keyboard::D: mIsMovingRight    = isPressed; break;
  }
}
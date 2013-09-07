#include "StringHelper.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include "Game.hpp"


// Intialize the game to run at 60 FPS
const sf::Time Game::FRAME_DURATION = sf::seconds(1.f / 60.f);

Game::Game()
: mWindow(sf::VideoMode(640, 480), "Desert Bloom", sf::Style::Close)
, mWorld(mWindow)
, mDevFont() // For development purposes only
, mDevText() // For development purposes only
, mDevUpdateTime() // For development purposes only
, mDevFrameCount(0) // For development purposes only
{
  mDevFont.loadFromFile("media/fonts/sansation.ttf"); // For development purposes only
  mDevText.setFont(mDevFont); // For development purposes only
  mDevText.setPosition(5.f, 5.f); // For development purposes only
  mDevText.setCharacterSize(10); // For development purposes only
}

void Game::run()
{
  sf::Clock clock;
  sf::Time elapsedTime = sf::Time::Zero;

  while (mWindow.isOpen()) {

    // Obtain the amount of time that has passed since the previous frame and add it to the counter
    sf::Time updateTime = clock.restart();
    elapsedTime += updateTime;

    while (elapsedTime > FRAME_DURATION) { // If more time has passed than the desired frame duration...
      elapsedTime -= FRAME_DURATION; // Store the overrunning time  // For development purposes only

      processEvents();
      update(FRAME_DURATION);
    }

    updateDevOutput(elapsedTime); // For development purposes only
    render();
  }
}

void Game::processEvents()
{
  sf::Event event;
  while (mWindow.pollEvent(event)) {
    switch (event.type) {
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

void Game::update(sf::Time frameDuration)
{
  mWorld.update(frameDuration);
}

void Game::render()
{
  mWindow.clear();
  mWorld.draw();

  mWindow.setView(mWindow.getDefaultView());
  mWindow.draw(mDevText);  // For development purposes only
  mWindow.display();
}

void Game::updateDevOutput(sf::Time elapsedTime)  // For development purposes only
{
  mDevUpdateTime += elapsedTime;
  mDevFrameCount ++;

  if (mDevUpdateTime >= sf::seconds(1.f)) {
    mDevText.setString(
      "WORK IN PROGRESS\n"
      "Build 0021\n"
      "FPS: " + toString(mDevFrameCount) + "\n" +
      "Frame duration: " + toString(mDevUpdateTime.asMicroseconds() / mDevFrameCount) + "us");

    mDevUpdateTime -= sf::seconds(1.f);
    mDevFrameCount = 0;
  }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
  if (key == sf::Keyboard::Escape)
    mWindow.close();
}
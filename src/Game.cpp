#include <string> // For development purposes only
#include "StringHelper.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include "Game.hpp"


// Intialize the game to run at 60 FPS
const sf::Time Game::FRAME_DURATION = sf::seconds(1.f / 60.f);

Game::Game(int argc, char** argv)
: mArgC(argc)
, mArgV(argv)
, mWindow(sf::VideoMode(640, 480), "Desert Bloom", sf::Style::Close)
, mWorld(mWindow)
, mIsFocused(true)
, mIcon() // For development purposes only
, mDevFont() // For development purposes only
, mDevText() // For development purposes only
, mDevUpdateTime() // For development purposes only
, mDevFrameCount(0) // For development purposes only
{
  mIcon.loadFromFile("media/textures/mushroom.png"); // For development purposes only
  mWindow.setIcon(mIcon.getSize().x, mIcon.getSize().y, mIcon.getPixelsPtr()); // For development purposes only

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

      processInput();

      if (mIsFocused)
        update(FRAME_DURATION);
    }

    updateDevOutput(elapsedTime); // For development purposes only
    render();
  }
}

void Game::processInput()
{
  CommandQueue& commands = mWorld.getCommandQueue();
  sf::Event event;

  mPlayer.handleRealtimeInput(commands);

  while (mWindow.pollEvent(event)) {
    mPlayer.handleEvent(event, commands);

    if (event.key.code == sf::Keyboard::Escape)
      mWindow.close();

    switch (event.type) {
      case sf::Event::GainedFocus:
        mIsFocused = true;
        break;
      case sf::Event::LostFocus:
        mIsFocused = false;
        break;
      case sf::Event::Closed:
        mWindow.close();
        break;
    }
  }
}

void Game::update(sf::Time frameDuration)
{
  /*sf::Vector2f movement(0.f, 0.f);
  float mPlayerSpeed = 0.f;
  sf::Sprite mPlayer;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    movement.y -= mPlayerSpeed;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    movement.y += mPlayerSpeed;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    movement.x -= mPlayerSpeed;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    movement.x += mPlayerSpeed;

  mPlayer.move(movement * frameDuration.asSeconds());*/
  mWorld.update(frameDuration);
}

void Game::render()
{
  mWindow.clear();
  mWorld.draw();

  mWindow.setView(mWindow.getDefaultView());

  if (!(mArgC >= 2 && std::string(mArgV[1]) == "-nodev")) // For development purposes only
    mWindow.draw(mDevText); // For development purposes only

  mWindow.display();
}

void Game::updateDevOutput(sf::Time elapsedTime)  // For development purposes only
{
  mDevUpdateTime += elapsedTime;
  mDevFrameCount ++;

  if (mDevUpdateTime >= sf::seconds(1.f)) {
    mDevText.setString(
      "WORK IN PROGRESS\n"
      "Build 0026\n"
      "Compiled with GCC G++ 4.8.0 (rev2)\n"
      "Linked with SFML 2.0\n\n"
      "FPS: " + toString(mDevFrameCount) + "\n" +
      "Frame duration: " + toString(mDevUpdateTime.asMicroseconds() / mDevFrameCount) + "us");

    mDevUpdateTime -= sf::seconds(1.f);
    mDevFrameCount = 0;
  }
}

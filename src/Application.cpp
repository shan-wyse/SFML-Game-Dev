#include "Application.hpp"
#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "TitleState.hpp"
#include "MenuState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"

Application::Application()
: mWindow(sf::VideoMode(640, 480), "Desert Bloom 2000", sf::Style::Close)
, mTextures()
, mFonts()
, mPlayer()
, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
, mIcon() // For development purposes only
, mDevText() // For development purposes only
, mDevUpdateTime() // For development purposes only
, mDevFrameCount(0) // For development purposes only
{
  mWindow.setKeyRepeatEnabled(false);

  mFonts.loadResource(Fonts::Main, "media/fonts/sansation.ttf");
  mTextures.loadResource(Textures::TitleScreen, "media/textures/title_screen.png");

  mIcon.loadFromFile("media/textures/mushroom.png"); // For development purposes only
  mWindow.setIcon(mIcon.getSize().x, mIcon.getSize().y, mIcon.getPixelsPtr()); // For development purposes only

  mDevText.setFont(mFonts.get(Fonts::Main)); // For development purposes only
  mDevText.setPosition(5.f, 5.f); // For development purposes only
  mDevText.setCharacterSize(10u); // For development purposes only

  registerStates();
  mStateStack.pushState(States::Title);
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
      update(FRAME_DURATION);

      if (mStateStack.isEmpty())
        mWindow.close();
    }

    updateDevOutput(updateTime); // For development purposes only
    render();
  }
}

void Application::processInput()
{
  sf::Event event;

  while (mWindow.pollEvent(event)) {
    mStateStack.processEvent();

    if (event.type == sf::Event::Closed)
      mWindow.close();
  }
}

void Application::update(sf::Time delta)
{
  mStateStack.update(delta);
}

void Application::render()
{
  mWindow.clear();

  mStateStack.draw();

  mWindow.setView(mWindow.getDefaultView());
  mWindow.draw(mDevText);

  mWindow.display();
}

void Application::registerStates()
{
  mStateStack.registerState<TitleState>     (States::Title);
  mStateStack.registerState<MenuState>      (States::Menu);
  mStateStack.registerState<GameState>      (States::Game);
  mStateStack.registerState<PauseState>     (States::Pause);
}

void Application::updateDevOutput(sf::Time elapsedTime)  // For development purposes only
{
  mDevUpdateTime += elapsedTime;
  mDevFrameCount++;

  if (mDevUpdateTime >= sf::seconds(1.f)) {
    mDevText.setString(
      "WORK IN PROGRESS\n"
      "Build 0027\n"
      "Compiled with GCC G++ 4.8.0 (rev2)\n"
      "Linked with SFML 2.0\n\n"
      "FPS: " + toString(mDevFrameCount) + "\n" +
      "Frame duration: " + toString(mDevUpdateTime.asMicroseconds() / mDevFrameCount) + "us");

    mDevUpdateTime -= sf::seconds(1.f);
    mDevFrameCount = 0;
  }
}

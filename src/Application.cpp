#include "Application.hpp"
#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "TitleState.hpp"
#include "MenuState.hpp"
#include "LoadingState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"

#include "StringHelper.hpp"

const sf::Time Application::FRAME_DURATION = sf::seconds(1.f / 60.f);

Application::Application(int argc, char** argv)
: mArgC(argc)
, mArgV(argv)
, mWindow(sf::VideoMode(640, 480), "Desert Bloom 2000", sf::Style::Close)
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

  mFonts.loadResource(Fonts::Id::Main, "media/fonts/sansation.ttf");
  mTextures.loadResource(Textures::Id::TitleScreen, "media/textures/title_screen.png");

  mIcon.loadFromFile("media/textures/mushroom.png"); // For development purposes only
  mWindow.setIcon(mIcon.getSize().x, mIcon.getSize().y, mIcon.getPixelsPtr()); // For development purposes only

  mDevText.setFont(mFonts.getResource(Fonts::Id::Main)); // For development purposes only
  mDevText.setPosition(5.f, 5.f); // For development purposes only
  mDevText.setCharacterSize(10u); // For development purposes only

  registerStates();
  mStateStack.pushState(States::Title);
}

void Application::run()
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

    updateDevOutput(elapsedTime); // For development purposes only
    render();
  }
}

void Application::processInput()
{
  sf::Event event;

  while (mWindow.pollEvent(event)) {
    mStateStack.processEvent(event);

    if (event.type == sf::Event::Closed)
      mWindow.close();
  }
}

void Application::update(sf::Time frameDuration)
{
  mStateStack.update(frameDuration);
}

void Application::render()
{
  mWindow.clear();
  mStateStack.render();

  mWindow.setView(mWindow.getDefaultView());
  if (!(mArgC >= 2 && std::string(mArgV[1]) == "-nodev")) // For development purposes only
    mWindow.draw(mDevText); // For development purposes only

  mWindow.display();
}

void Application::registerStates()
{
  mStateStack.registerState<TitleState>     (States::Title);
  mStateStack.registerState<MenuState>      (States::Menu);
  mStateStack.registerState<LoadingState>   (States::Loading);
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
      "Build 0029\n"
      "Compiled with GCC G++ 4.8.0 (rev2)\n"
      "Linked with SFML 2.0\n\n"
      "FPS: " + toString(mDevFrameCount) + "\n" +
      "Frame duration: " + toString(mDevUpdateTime.asMicroseconds() / mDevFrameCount) + "us");

    mDevUpdateTime -= sf::seconds(1.f);
    mDevFrameCount = 0;
  }
}

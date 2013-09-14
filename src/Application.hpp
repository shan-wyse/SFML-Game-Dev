#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "StateStack.hpp"
#include "Player.hpp"
#include "ResourceManager.hpp"
#include "ResourceIdentifiers.hpp" // CHECK

class Application
{
public:
                              Application();
  void                        run();

private:

  void                        processInput();
  void                        update(sf::Time delta);
  void                        render();

  void                        registerStates();

  void                        updateDevOutput(sf::Time elapsedTime);

  static const sf::Time       FRAME_DURATION;

  int                         mArgC;
  char**                      mArgV;

  sf::RenderWindow            mWindow;
  TextureManager              mTextures;
  FontManager                 mFonts;
  Player                      mPlayer;
  StateStack                  mStateStack;

  sf::Image                   mIcon; // For development purposes only

  sf::Text                    mDevText; // For development purposes only
  sf::Time                    mDevUpdateTime; // For development purposes only
  std::size_t                 mDevFrameCount; // For development purposes only
};

#endif // APPLICATION_HPP

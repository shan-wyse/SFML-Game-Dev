// Application.hpp


#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "StateStack.hpp"
#include "Player.hpp"
#include "ResourceManager.hpp"
#include "ResourceIdentifiers.hpp" // CHECK
#include "MusicPlayer.hpp"
#include "SoundPlayer.hpp"


class Application
{
public:
                              Application(int argc, const char** argv);
  void                        run();

private:

  void                        processInput();
  void                        update(sf::Time frameDuration);
  void                        render();
  void                        registerStates();

  void                        updateDevOutput(sf::Time elapsedTime);

  static const sf::Time       FRAME_DURATION;

  int                         mArgC;
  const char**                mArgV;
  sf::RenderWindow            mWindow;
  sf::Image                   mIcon; // For development purposes only
  StateStack                  mStateStack;
  Player                      mPlayer;
  TextureManager              mTextures;
  FontManager                 mFonts;
  MusicPlayer                 mMusicPlayer;
  SoundPlayer                 mSoundPlayer;

  sf::Text                    mDevText; // For development purposes only
  sf::Time                    mDevUpdateTime; // For development purposes only
  std::size_t                 mDevFrameCount; // For development purposes only
};

#endif // APPLICATION_HPP

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "World.hpp"

class Game : private sf::NonCopyable
{
public:
	                            Game(int argc, char* argv[]);
	void                        run();

private:
	void				                processEvents();
	void				                update(sf::Time frameDuration);
	void				                render();

  void                        updateDevOutput(sf::Time elapsedTime);
  void                        handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

  static const sf::Time       FRAME_DURATION;

  int                         mArgC;
  char**                      mArgV;

	sf::RenderWindow	          mWindow;
  World                       mWorld;
  bool                        mIsFocused;
  sf::Image                   mIcon; // For development purposes only

  sf::Font                    mDevFont; // For development purposes only
  sf::Text                    mDevText; // For development purposes only
  sf::Time                    mDevUpdateTime; // For development purposes only
  std::size_t                 mDevFrameCount; // For development purposes only
};

#endif // GAME_HPP
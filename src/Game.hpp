#ifndef GAME_HPP
#define GAME_HPP

// #include <SFML/Graphics.hpp>
// #include "TextureManager.hpp"

#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "World.hpp"

class Game : private sf::NonCopyable
{
public:
	                            Game();
	void                        run();

private:
	void				                processEvents();
	void				                update(sf::Time deltaTime);
	void				                render();

  void                        handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

  static const sf::Time       FRAME_DURATION;

	sf::RenderWindow	          mWindow;
  World                       mWorld;

  sf::Font                    mDevFont;
  sf::Text                    mDevText;
  sf::Time                    mDevUpdateTime;
  std::size_t                 mDevFrameCount;

  /*sf::Texture         mTexture;
  TextureManager      mTextures;
	sf::Sprite          mPlayer;

  bool                mIsMovingUp;
  bool                mIsMovingDown;
  bool                mIsMovingLeft;
  bool                mIsMovingRight;*/
};

#endif // GAME_HPP
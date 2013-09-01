#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	void                run();

private:
	void				        processEvents();
	void				        update(sf::Time deltaTime);
	void				        render();

  void                handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	sf::RenderWindow	  mWindow;
  sf::Texture         mTexture;
	sf::Sprite          mPlayer;

  bool                mIsMovingUp;
  bool                mIsMovingDown;
  bool                mIsMovingLeft;
  bool                mIsMovingRight;
};

#endif
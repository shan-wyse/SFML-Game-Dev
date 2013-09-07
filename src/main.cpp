#include <stdexcept>
#include <iostream>

#include "Game.hpp"

int main()
{
  try {
    Game game;
    game.run();
  } catch (std::exception& exc) {
    std::cout << "\nEXCEPTION: " << exc.what() << std::endl;
  }
}
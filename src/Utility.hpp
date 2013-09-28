#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <sstream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

namespace sf
{
  class Sprite;
  class Text;
}

class Utility
{
public:
  static int              randomInt(int exclusiveMax);

  static float            toDegree(float radian);
  static float            toRadian(float degree);

  static float            vectorLength(sf::Vector2f vector);
  static sf::Vector2f     unitVector(sf::Vector2f vector);
};

#endif // UTILITY_HPP

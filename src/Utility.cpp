#include <random>
#include <cmath>
#include <ctime>
#include <cassert>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Utility.hpp"

namespace
{
  std::default_random_engine createRandomEngine()
  {
    auto seed = static_cast<unsigned long> (std::time(nullptr));
    return std::default_random_engine(seed);
  }

  auto RandomEngine = createRandomEngine();
}

int Utility::randomInt(int exclusiveMax)
{
  std::uniform_int_distribution<> distribution(0, exclusiveMax - 1);
  return distribution(RandomEngine);
}

float Utility::toDegree(float radian)
{
  return 180.f / 3.141592653589793238462643383f * radian;
}

float Utility::toRadian(float degree)
{
  return 3.141592653589793238462643383f / 180.f * degree;
}

float Utility::vectorLength(sf::Vector2f vector)
{
  return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f Utility::unitVector(sf::Vector2f vector)
{
  assert (vector != sf::Vector2f(0.f, 0.f));
  return vector / vectorLength(vector);
}

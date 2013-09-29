#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>

struct Particle
{
  enum              Type { Propellant, Smoke, Count };

  sf::Vector2f      position;
  sf::Color         color;
  sf::Time          lifetime;
};

#endif // PARTICLE_HPP

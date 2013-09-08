#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "CommandQueue.hpp"

class Player
{
public:
  void      handleRealtimeInput(CommandQueue& commands);
  void      handleEvent(const sf::Event& event, CommandQueue& commands);
};

#endif

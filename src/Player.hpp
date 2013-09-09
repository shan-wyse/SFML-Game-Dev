#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "CommandQueue.hpp"

class Player
{
public:
  enum class                              Action { MoveUp, MoveDown, MoveLeft, MoveRight };

  void                                    handleRealtimeInput(CommandQueue& commands);
  void                                    handleEvent(const sf::Event& event, CommandQueue& commands);

  void                                    setAssignedKey(Action action, sf::Keyboard::Key key);
  sf::Keyboard::Key                       getAssignedKey(Action action) const;

private:
  static bool                             isRealtimeAction();

  std::map<sf::Keyboard::Key, Action>     mKeyBinding;
  std::map<Action, Command>               mActionBinding;
};

#endif

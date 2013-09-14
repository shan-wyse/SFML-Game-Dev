#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "CommandQueue.hpp"
#include "Category.hpp"

class Player
{
public:
  enum class                              Action { MoveUp, MoveDown, MoveLeft, MoveRight, Close };
                                          Player();

  void                                    handleRealtimeInput(CommandQueue& commands);
  void                                    handleEvent(const sf::Event& event, CommandQueue& commands);

  void                                    setAssignedKey(Action action, sf::Keyboard::Key key);
  sf::Keyboard::Key                       getAssignedKey(Action action) const;

private:
  void                                    initializeActions();
  static bool                             isRealtimeAction(Action action);

  std::map<sf::Keyboard::Key, Action>     mKeyBinding;
  std::map<Action, Command>               mActionBinding;
};

#endif // PLAYER_HPP

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <map>
#include <SFML/Window/Event.hpp>
#include "Command.hpp"
#include <SFML/Window/Keyboard.hpp>
// #include "CommandQueue.hpp"
// #include "Category.hpp"

class CommandQueue;

class Player
{
public:
  enum                                    Action
                                          {
                                            MoveUp,
                                            MoveDown,
                                            MoveLeft,
                                            MoveRight,
                                            Fire,
                                            LaunchMissile,

                                            Count
                                          };

  enum                                    MissionStatus
                                          {
                                            MissionInProgress,
                                            MissionSuccess,
                                            MissionFailure
                                          };

                                          Player(sf::TcpSocket* socket, sf::Int32 identifer, const KeyBinding* keyBinding);

  void                                    handleRealtimeInput(CommandQueue& commands); // process
  void                                    handleEvent(const sf::Event& event, CommandQueue& commands);

  void                                    setAssignedKey(Action action, sf::Keyboard::Key key);
  sf::Keyboard::Key                       getAssignedKey(Action action) const;

  void                                    setMissionStatus(MissionStatus status);
  MissionStatus                           getMissionStatus() const;

private:
  void                                    initializeActions();
  static bool                             isRealtimeAction(Action action);

  std::map<sf::Keyboard::Key, Action>     mKeyBinding;
  std::map<Action, Command>               mActionBinding;
  MissionStatus                           mCurrentMissionStatus;
};

#endif // PLAYER_HPP

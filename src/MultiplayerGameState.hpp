#ifndef MULTIPLAYER_GAME_STATE
#define MULTIPLAYER_GAME_STATE

class MultiplayerGameState : public State
{
public:
                                    MultiplayerGameState(StateStack& stack, Context context, bool isHost);

  virtual bool                      processEvent(const sf::Event& event);
  virtual bool                      update(sf::Time delta);
  virtual void                      render();

private:
  typedef std::unique_ptr<Player>   PlayerPtr;

  void                              updateBroadcastMessage(sf::Time elapsedTime);
  void                              processPacket(sf::Int32 packetType, sf::Packet& packet);

  World                             mWorld;
  sf::RenderWindow&                 mWindow;
  TextureManager&                   mTextureManager;

  std::map<int, PlayerPtr>          mPlayers;
  std::vector<sf::Int32>            mLocalPlayerIdentifiers;
  sf::TcpSocket                     mSocket;
  bool                              bConnected;
  std::unique_ptr<GameServer>       mGameServer;
  sf::Clock                         mTickClock;

  std::vector<std::string>          mBroadcasts;
  sf::Text                          mBroadcastText;
  sf::Time                          mBroadcastElapsedTime;
};

#endif // MULTIPLAYER_GAME_STATE

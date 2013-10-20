#ifndef NETWORK_PROTOCOL_HPP
#define NETWORK_PROTOCOL_HPP

namespace Server
{
  enum PacketType
  {
    BroadcastMessage,
    SpawnSelf,
    InitialEvent,
    PlayerEvent,
    PlayerRealtimeChange,
    PlayerConnect,
    PlayerDisconnect,
    AcceptCoopPartner,
    SpawnEnemy,
    SpawnPickup,
    UpdateClientState,
    MissionSuccess
  };
}

namespace Client
{
  enum PacketType
  {
    PlayerEvent,
    Quit,
    PlayerRealtimeChange,
    RequestCoopPartner,
    PositionUpdate,
    GameEvent
  }
}

class NetworkProtocol
{
  // empty
};

#endif // NETWORK_PROTOCOL_HPP

#include "MultiplayerGameState.hpp"

MultiplayerGameState::MultiplayerGameState()
{
  sf::IpAddress ipAddress;

  if (isHost) {
    mGameServer.reset(new GameServer());
    ipAddress = "127.0.0.1";
  } else
    ipAddress = getAddressFromFile();

  if (mSocket.connect(ipAddress, serverPort, sf::seconds(5.f)) == sf::TcpSocket::Done)
    bConnected = true;
  else
    mFailedConnectionClock.restart();

  mSocket.setBlocking(false);
}

bool MultiplayerGameState::update(sf::Time delta)
{
  sf::Packet packet;
  if (mSocket.receive(packet) == sf::Socket::Done) {
    sf::Int32 packetType;
    packet >> packetType;
    processPacket(packetType, packet);
  }

  updateBroadcastMessage(delta);

  mPlayerInvitationTime += delta;
  if (mPlayerInvitationTime > sf::seconds(1.f))
    mPlayerInvitationTime = sf::Time::Zero;

  if (mTickClock.getElapsedTime() > sf::seconds(1.f / 20.f)) {
    sf::Packet positionUpdatePacket;
    positionUpdatePacket << static_cast<sf::Int32> (Client::PositionUpdate);
    positionUpdatePacket << static_cast<sf::Int32> (mLocalPlayerIdentifiers.size());

    for (sf::Int32 identifier : mLocalPlayerIdentifiers) {
      if (Aircraft* aircraft = mWorld.getAircraft(identifier))
        positionUpdatePacket << identifier << aircraft->getPosition().x << aircraft.getPosition().y;
    }

    mSocket.send(positionUpdatePacket);
    mTickClock.restart();
  }

  GameActions::Action gameAction;

  while (mWorld.pollGameAction(gameAction)) {
    sf::Packet packet;
    packet << static_cast<sf::Int32> (Client::GameEvent);
    packet << static_cast<sf::Int32> (gameAction.type);
    packet << gameAction.position.x;
    packet << gameAction.position.y;

    mSocket.send(packet);
  }
}

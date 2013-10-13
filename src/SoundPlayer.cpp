#include <cmath>
#include <SFML/Audio/Listener.hpp>
#include "SoundPlayer.hpp"

namespace
{
  const float Z_LISTENER      = 300.f;
  const float ATTENUATION     = 8.f;
  const float MIN_DISTANCE_2D = 200.f;
  const float MIN_DISTANCE_3D = std::sqrt(MIN_DISTANCE_2D * MIN_DISTANCE_2D + Z_LISTENER * Z_LISTENER);
}

SoundPlayer::SoundPlayer()
: mSoundManager()
, mSounds()
{
  mSoundManager.loadResource(SoundEffects::AlliedGunfire,   "media/sounds/allied_gunfire.wav");
  mSoundManager.loadResource(SoundEffects::EnemyGunfire,    "media/sounds/enemy_gunfire.wav");
  mSoundManager.loadResource(SoundEffects::Explosion1,      "media/sounds/explosion1.wav");
  mSoundManager.loadResource(SoundEffects::Explosion2,      "media/sounds/explosion2.wav");
  mSoundManager.loadResource(SoundEffects::LaunchMissile,   "media/sounds/launch_missile.wav");
  mSoundManager.loadResource(SoundEffects::CollectPickup,   "media/sounds/collect_pickup.wav");
  mSoundManager.loadResource(SoundEffects::Button,          "media/sounds/button.wav");

  sf::Listener::setDirection(0.f, 0.f, -1.f);
}

void SoundPlayer::play(SoundEffects::Id effect)
{
  play(effect, getListenerPosition());
}

void SoundPlayer::play(SoundEffects::Id effect, sf::Vector2f position)
{
  mSounds.push_back(sf::Sound());
  sf::Sound& sound = mSounds.back();

  sound.setBuffer(mSoundManager.getResource(effect));
  sound.setPosition(position.x, -position.y, 0.f);
  sound.setAttenuation(ATTENUATION);
  sound.setMinDistance(MIN_DISTANCE_3D);

  sound.play();
}

void SoundPlayer::removeStoppedSounds()
{
  mSounds.remove_if([] (const sf::Sound& sound) { return sound.getStatus() == sf::Sound::Stopped; } );
}

void SoundPlayer::setListenerPosition(sf::Vector2f position)
{
  sf::Listener::setPosition(position.x, -position.y, Z_LISTENER);
}

sf::Vector2f SoundPlayer::getListenerPosition() const
{
  sf::Vector3f position = sf::Listener::getPosition();
  return sf::Vector2f(position.x, -position.y);
}

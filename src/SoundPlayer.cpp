#include <cmath>
#include <SFML/Audio/Listener.hpp>
#include "SoundPlayer.hpp"

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
}

void SoundPlayer::play(SoundEffects::Id effect)
{
  mSounds.push_back(sf::Sound(mSoundManager.getResource(effect)));
  mSounds.back().play();
}

void SoundPlayer::removeStoppedSounds()
{
  mSounds.remove_if([] (const sf::Sound& sound) { return sound.getStatus() == sf::Sound::Stopped; } );
}

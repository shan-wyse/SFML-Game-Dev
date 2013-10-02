#ifndef SOUND_PLAYER_HPP
#define SOUND_PLAYER_HPP

#include <list>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "ResourceManager.hpp"
#include "ResourceIdentifiers.hpp"

class SoundPlayer : private sf::NonCopyable
{
public:
                          SoundPlayer();

  void                    play(SoundEffects::Id effect);
  void                    play(SoundEffects::Id effect, sf::Vector2f position);

  void                    removeStoppedSounds();
  void                    setListenerPosition(sf::Vector2f position);

  sf::Vector2f            getListenerPosition() const;

private:
  SoundManager            mSoundManager;
  std::list<sf::Sound>    mSounds;
};

#endif // SOUND_PLAYER_HPP

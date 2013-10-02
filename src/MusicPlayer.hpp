#ifndef MUSIC_PLAYER_HPP
#define MUSIC_PLAYER_HPP

#include <map>
#include <string>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>
#include "ResourceManager.hpp"
#include "ResourceIdentifiers.hpp"

class MusicPlayer : private sf::NonCopyable
{
public:
                                      MusicPlayer();

  void                                play(Music::Id theme);
  void                                stop();

  void                                setPaused(bool paused);
  void                                setVolume(float volume);

  void                                transitionTo(Music::Id theme, sf::Time transitionDuration);

private:
  sf::Music                           mMusic;
  std::map<Music::Id, std::string>    mFilenames;
  float                               mVolume;
};

#endif // MUSIC_PLAYER_HPP

#include "MusicPlayer.hpp"

MusicPlayer::MusicPlayer()
: mMusic()
, mFilenames()
, mVolume(100.f)
{
  mFilenames[Music::MenuTheme]    = "media/music/menu_theme.ogg";
  mFilenames[Music::MissionTheme] = "media/music/mission_theme.ogg";
}

void MusicPlayer::play(Music::Id theme)
{
  std::string filename = mFilenames[theme];

  if (!mMusic.openFromFile(filename))
    throw std::runtime_error("Music theme " + filename + " could not be loaded.");

  mMusic.setVolume(mVolume);
  mMusic.setLoop(true);
  mMusic.play();
}

void MusicPlayer::stop()
{
  mMusic.stop();
}

void MusicPlayer::setPaused(bool pause)
{
  if (pause)
    mMusic.pause();
  else
    mMusic.play();
}

#ifndef SOUND_NODE_HPP
#define SOUND_NODE_HPP

#include "SceneNode.hpp"
#include "ResourceIdentifiers.hpp"

class SoundPlayer;

class SoundNode : public SceneNode
{
public:
  explicit                SoundNode(SoundPlayer& soundPlayer);

  void                    playSound(SoundEffects::Id sound, sf::Vector2f position);
  virtual unsigned int    getCategory() const;

private:
  SoundPlayer&            mSoundPlayer;
};

#endif // SOUND_NODE_HPP

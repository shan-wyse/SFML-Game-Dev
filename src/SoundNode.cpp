#include "SoundNode.hpp"
#include "SoundPlayer.hpp"

SoundNode::SoundNode(SoundPlayer& soundPlayer)
: SceneNode()
, mSoundPlayer(soundPlayer)
{
  // empty
}

void SoundNode::playSound(SoundEffects::Id sound, sf::Vector2f position)
{
  mSoundPlayer.play(sound, position);
}

unsigned int SoundNode::getCategory() const { return Category::SoundEffect; }

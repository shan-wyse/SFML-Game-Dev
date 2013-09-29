#ifndef EMITTER_NODE_HPP
#define EMITTER_NODE_HPP

#include "SceneNode.hpp"
#include "Particle.hpp"

class ParticleNode;

class EmitterNode : public SceneNode
{
public:
  explicit          EmitterNode(Particle::Type type);

private:
  virtual void      updateCurrent(sf::Time delta, CommandQueue& commands);
  void              emitParticles(sf::Time delta);

  sf::Time          mAccumulatedTime;
  Particle::Type    mType;
  ParticleNode*     mParticleSystem;
};

#endif // EMITTER_NODE_HPP

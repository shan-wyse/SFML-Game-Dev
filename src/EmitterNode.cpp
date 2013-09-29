#include "EmitterNode.hpp"
#include "ParticleNode.hpp"
#include "CommandQueue.hpp"
#include "Command.hpp"

EmitterNode::EmitterNode(Particle::Type type)
: SceneNode()
, mAccumulatedTime(sf::Time::Zero)
, mType(type)
, mParticleSystem(nullptr)
{
  // empty
}

void EmitterNode::updateCurrent(sf::Time delta, CommandQueue& commands)
{
  if (mParticleSystem)
    emitParticles(delta);
  else {
    auto finder = [this] (ParticleNode& container, sf::Time)
    {
      if (container.getParticleType() == mType)
        mParticleSystem = &container;
    };

    Command command;
    command.category = Category::ParticleSystem;
    command.action = derivedAction<ParticleNode> (finder);

    commands.push(command);
  }
}

void EmitterNode::emitParticles(sf::Time delta)
{
  const float emissionRate = 30.f;
  const sf::Time interval = sf::seconds(1.f) / emissionRate;

  mAccumulatedTime += delta;

  while (mAccumulatedTime > interval) {
    mAccumulatedTime -= interval;
    mParticleSystem->addParticle(getWorldPosition());
  }
}

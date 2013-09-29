#ifndef PARTICLE_NODE_HPP
#define PARTICLE_NODE_HPP

#include <deque>
#include <SFML/Graphics/VertexArray.hpp>
#include "SceneNode.hpp"
#include "Particle.hpp"
#include "ResourceIdentifiers.hpp"

class ParticleNode : public SceneNode
{
public:
                            ParticleNode(Particle::Type type, const TextureManager& textures);

  void                      addParticle(sf::Vector2f position);
  Particle::Type            getParticleType() const;

  virtual unsigned int      getCategory() const;

private:
  virtual void              updateCurrent(sf::Time delta, CommandQueue& commands);
  virtual void              drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

  void                      computeVertices() const;
  void                      addVertex(float worldX, float worldY, float texCoordX, float texCoordY, const sf::Color& color) const;

  std::deque<Particle>      mParticles;
  const sf::Texture&        mTexture;
  Particle::Type            mType;

  mutable sf::VertexArray   mVertexArray;
  mutable bool              bRequiresVertexUpdate;
};

#endif // PARTICLE_NODE_HPP

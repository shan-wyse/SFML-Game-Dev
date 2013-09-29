#include <algorithm>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "ParticleNode.hpp"
#include "DataTables.hpp"
#include "ResourceManager.hpp"

namespace { const std::vector<ParticleData> Table = initializeParticleData(); }

ParticleNode::ParticleNode(Particle::Type type, const TextureManager& textures)
: SceneNode()
, mTexture(textures.getResource(Textures::Id::Particle))
{
  // empty
}

void ParticleNode::addParticle(sf::Vector2f position)
{
  Particle particle;
  particle.position = position;
  particle.color = Table[mType].color;
  particle.lifetime = Table[mType].lifetime;

  mParticles.push_back(particle);
}

Particle::Type ParticleNode::getParticleType() const { return mType; }

unsigned int ParticleNode::getCategory() const { return Category::ParticleSystem; }

void ParticleNode::updateCurrent(sf::Time delta, CommandQueue&)
{
  while (!mParticles.empty() && mParticles.front().lifetime <= sf::Time::Zero)
    mParticles.pop_front();

  for (Particle& particle : mParticles)
    particle.lifetime -= delta;

  bRequiresVertexUpdate = true;
}

void ParticleNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
  if (bRequiresVertexUpdate) {
    computeVertices();
    bRequiresVertexUpdate = false;
  }

  states.texture = &mTexture;
  target.draw(mVertexArray, states);
}

void ParticleNode::computeVertices() const
{
  sf::Vector2f size(mTexture.getSize());
  sf::Vector2f half = size / 2.f;

  mVertexArray.clear();

  for (const Particle& particle : mParticles) {
    sf::Vector2f position = particle.position;
    sf::Color color = particle.color;

    float ratio = particle.lifetime.asSeconds() / Table[mType].lifetime.asSeconds();
    color.a = static_cast<sf::Uint8> (255 * std::max(ratio, 0.f));

    addVertex(position.x - half.x, position.y - half.y, 0.f, 0.f, color);
    addVertex(position.x + half.x, position.y - half.y, 0.f, 0.f, color);
    addVertex(position.x + half.x, position.y + half.y, 0.f, 0.f, color);
    addVertex(position.x - half.x, position.y + half.y, 0.f, 0.f, color);
  }
}

void ParticleNode::addVertex(float worldX, float worldY, float texCoordX, float texCoordY, const sf::Color& color) const
{
  sf::Vertex vertex;
  vertex.position = sf::Vector2f(worldX, worldY);
  vertex.texCoords = sf::Vector2f(texCoordX, texCoordY);
  vertex.color = color;

  mVertexArray.append(vertex);
}

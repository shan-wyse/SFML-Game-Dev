#include "TextureManager.hpp"

void TextureManager::loadTexture(Textures::ID id, const std::string& filename)
{
  std::unique_ptr<sf::Texture> texture(new sf::Texture());
  if (!texture->loadFromFile(filename))
    throw std::runtime_error("TextureManager::loadTexture() - Failed to load " + filename);

  auto inserted = mTextureMap.insert(std::make_pair(id, std::move(texture)));
  assert(inserted.second);
}

sf::Texture& TextureManager::getTexture(Textures::ID id)
{
  auto texture = mTextureMap.find(id)
  assert(found != mTextureMap.end());
  return *found->second;
}
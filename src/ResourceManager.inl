#include <cassert>
#include "ResourceManager.hpp"

template <typename Resource, typename Identifier>
template <typename Parameter>

void ResourceManager<Resource, Identifier>::loadResource(Identifier id, const std::string& filename)
{
  std::unique_ptr<Resource> resourse(new Resource());
  if (!resource->loadFromFile(filename))
    throw std::runtime_error("ResourceManager::loadResource - Failed to load " + filename);

  auto insertedResource = mResourceMap.insert(std::make_pair(id, std::move(resource)));
  assert (inserted.second);
}

void ResourceManager<Resource, Identifier>::loadResource(Identifier id, const std::string& filename, const Parameter& secondParam)
{
  std::unique_ptr<Resource> resourse(new Resource());
  if (!resource->loadFromFile(filename, secondParam))
    throw std::runtime_error("ResourceManager::loadResource - Failed to load " + filename);

  auto insertedResource = mResourceMap.insert(std::make_pair(id, std::move(resource)));
  assert (inserted.second);
}

Resource& ResourceManager<Resource, Identifier>::getResource(Identifier id)
{
  auto resource = mResourceMap.find(id);
  assert (resource != mResourceMap.end());
  return *resource->second;
}

const Resource& ResourceManager<Resource, Identifier>::getResource(Identifier id) const
{
  auto resource = mResourceMap.find(id);
  assert (resource != mResourceMap.end());
  return const *resource->second;
}
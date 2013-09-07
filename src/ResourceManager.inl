template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::loadResource(Identifier id, const std::string& filename)
{
  std::unique_ptr<Resource> resource(new Resource());
  if (!resource->loadFromFile(filename))
    throw std::runtime_error("ResourceManager::loadResource - Failed to load " + filename);

  insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceManager<Resource, Identifier>::loadResource(Identifier id, const std::string& filename, 
    const Parameter& additionalParam)
{
  std::unique_ptr<Resource> resource(new Resource());
  if (!resource->loadFromFile(filename, additionalParam))
    throw std::runtime_error("ResourceManager::loadResource - Failed to load " + filename);

  insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
Resource& ResourceManager<Resource, Identifier>::getResource(Identifier id)
{
  auto resource = mResourceMap.find(id);
  assert (resource != mResourceMap.end());

  return *resource->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceManager<Resource, Identifier>::getResource(Identifier id) const
{
  auto resource = mResourceMap.find(id);
  assert (resource != mResourceMap.end());

  return *resource->second;
}

template <typename Resource, typename Identifier>
void ResourceManager<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource)
{
  auto insertedResource = mResourceMap.insert(std::make_pair(id, std::move(resource)));
  assert (insertedResource.second);
}
#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <string>
#include <memory>
#include <map>
#include <stdexcept>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceManager
{
public:
  void                                              loadResource(Identifier id, const std::string& filename);

  template <typename Parameter>
  void                                              loadResource(Identifier id, const std::string& filename, 
                                                        const Parameter& additionalParam);
  
  Resource&                                         getResource(Identifier id);
  const Resource&                                   getResource(Identifier id) const;

private:
  void                                              insertResource(Identifier id, std::unique_ptr<Resource> resource);

  std::map<Identifier, std::unique_ptr<Resource>>   mResourceMap;
};

#include "ResourceManager.inl"
#endif // RESOURCE_MANAGER_HPP
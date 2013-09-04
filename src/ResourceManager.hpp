#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

template <typename Resource, typename Identifier>

class ResourceManager
{
public:
  template <typename Parameter>
  void                                                loadResource(Indentifier id, const std::string& filename);
  void                                                loadResource(Indentifier id, const std::string& filename, const Parameter& secondParam);
  Resource&                                           getResource(Identifier id);
  const Resource&                                     getResource(Identifier id) const;

private:
  std::map<Identifier, std::unique_ptr<Resource>>     mResourceMap);
};

#include ResourceManager.inl

#endif
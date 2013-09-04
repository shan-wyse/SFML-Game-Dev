#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include "Entity.hpp"

class Aircraft : public Entity
{
public:
  enum Type { Eagle, Raptor };
  explicit      Aircraft(Type type);

private:
  Type          mType;  
};

#endif
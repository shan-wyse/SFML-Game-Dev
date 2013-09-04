#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

class Aircraft : public Entity
{
public:
  enum Type { Eagle, Raptor };
  explicit      Aircraft(Type type);

private:
  Type          mType;  
};

#endif
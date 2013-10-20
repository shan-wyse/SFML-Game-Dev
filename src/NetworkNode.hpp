#ifndef NETWORK_NODE_HPP
#define NETWORK_NODE_HPP

namespace GameActions
{
  enum Type { EnemyExplode };

  struct Action
  {
                    Action()
                    Action(Type type, sf::Vector2f position);

    Type            type;
    sf::Vector2f    position;
  };
}

class NetworkNode : public SceneNode
{
public:
                                      NetworkNode();

  void                                notifyGameActions(GameActions::Type type, sf::Vector2f position);
  bool                                pollGameActions(GameActions::Info& out);

private:
    std::queue<GameActions::Action>   mPendingActions;
};

#endif // NETWORK_NODE_HPP

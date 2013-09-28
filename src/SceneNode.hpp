#ifndef SCENE_NODE_HPP
#define SCENE_NODE_HPP

#include <memory>
#include <vector>
#include <set>
#include <utility>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "Command.hpp"

struct  Command;
class   CommandQueue;

class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
  typedef std::unique_ptr<SceneNode>          NodePtr;
  typedef std::pair<SceneNode*, SceneNode*>   NodePair;
  // enum Layer                            { Background, Foreground, LayerCount };

  explicit                                    SceneNode();

  void                                        attachChild(NodePtr child);
  NodePtr                                     detachChild(const SceneNode& node);

  void                                        update(sf::Time delta, CommandQueue& commands);

  sf::Vector2f                                getWorldPosition() const;
  sf::Transform                               getWorldTransform() const;

  virtual unsigned int                        getCategory() const;
  void                                        onCommand(const Command& command, sf::Time delta);

  void                                        checkSceneCollision(SceneNode& sceneGraph, std::set<NodePair>& collissionPairs);
  void                                        checkNodeCollision(SceneNode& node, std::set<NodePair>& collissionPairs);
  void                                        removeWrecks();

  virtual sf::FloatRect                       getBoundingRect() const;
  virtual bool                                isMarkedForRemoval() const;
  virtual bool                                isDestroyed() const;

private:
  virtual void                                updateCurrent(sf::Time delta, CommandQueue& commands);
  void                                        updateChildren(sf::Time delta, CommandQueue& commands);

  virtual void                                draw(sf::RenderTarget& target, sf::RenderStates states) const final;
  virtual void                                drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
  void                                        drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
  void                                        drawBoundingRect(sf::RenderTarget& target, sf::RenderStates states) const;

  SceneNode*                                  mParent;
  std::vector<NodePtr>                        mChildren;
  Category::Type                              mDefaultCategory;
};

bool                                          collision(const SceneNode& a, const SceneNode& b);
bool                                          distance(const SceneNode& a, const SceneNode& b);

#endif // SCENE_NODE_HPP

#ifndef SCENE_NODE_HPP
#define SCENE_NODE_HPP

#include <memory>

class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
  typedef std::unique_ptr<SceneNode>    NodePtr;
  enum Layer                            { Background, Foreground, LayerCount };

  SceneNode();

  void                                  attachChild(NodePtr child);
  NodePtr                               detachChild(const SceneNode& node);

private:
  final virtual void                    draw(sf::RenderTarget& target, sf::RenderStates states) const;
  virtual void                          drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
  std::vector<NodePtr>                  mChildren;
  SceneNode*                            mParent;
};

#endif
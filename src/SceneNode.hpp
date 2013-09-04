#ifndef SCENE_NODE_HPP
#define SCENE_NODE_HPP

#include <memory>

class SceneNode
{
public:
  typedef std::unique_ptr<SceneNode>    NodePtr;
  SceneNode();

  void                                  attachChild(NodePtr child);
  NodePtr                               detachChild(const SceneNode& node);

private:
  std::vector<NodePtr>                  mChildren;
  SceneNode*                            mParent;
};

#endif
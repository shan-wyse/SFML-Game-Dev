#include <vector>
#include "SceneNode.hpp"

SceneNode::SceneNode()
: mParent(nullptr)
{
  // empty
}

void SceneNode::attachChild(NodePtr child)
{
  child->mParent = this;
  mChildren.push_back(std::move(child));
}
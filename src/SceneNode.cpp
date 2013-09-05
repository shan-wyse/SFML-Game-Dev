#include <vector>
#include <cassert>
#include <SFML/Graphics.hpp>
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

SceneNode::NodePtr SceneNode::detachChild(const SceneNode& node)
{
  auto foundNode = std::find_if(mChildren.begin(), mChildren.end(), [&] (NodePtr& p) -> bool { return p.get() == &node; });
  assert (foundNode != mChildren.end());

  NodePtr detachedNode = std::move(*foundNode);
  detachedNode->mParent = nullptr;
  mChildren.erase(foundNode);
  return detachedNode;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  drawCurrent(target, states);

  for (const NodePtr child : mChildren)
    child->draw(target, states);
}
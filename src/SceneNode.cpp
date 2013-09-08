#include <algorithm>
#include <cassert>
#include "SceneNode.hpp"
#include "Category.hpp"

SceneNode::SceneNode()
: mParent(nullptr)
, mChildren()
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
  auto foundNode = std::find_if(mChildren.begin(), mChildren.end(), [&] (NodePtr& p) ->
      bool { return p.get() == &node; });

  assert (foundNode != mChildren.end());

  NodePtr detachedNode = std::move(*foundNode);
  detachedNode->mParent = nullptr;
  mChildren.erase(foundNode);
  return detachedNode;
}

void SceneNode::update(sf::Time delta)
{
  updateCurrent(delta);
  updateChildren(delta);
}

sf::Transform SceneNode::getWorldTransform() const
{
  sf::Transform transform = sf::Transform::Identity;

  for (const SceneNode* node = this; node != nullptr; node = node->mParent)
    transform *= node->getTransform();

  return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
  return getWorldTransform() * sf::Vector2f();
}

unsigned int SceneNode::getCategory() const
{
  return Category::Scene;
}

void SceneNode::onCommand(const Command& command, sf::Time delta)
{
  if (command.category & getCategory()) // possible refactor
    command.action(*this, delta);

  for (NodePtr& child : mChildren)
    child->onCommand(command, delta);
}

void SceneNode::updateCurrent(sf::Time delta)
{
  // empty
}

void SceneNode::updateChildren(sf::Time delta)
{
  for (NodePtr& child : mChildren)
    child->update(delta);
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();

  drawCurrent(target, states);
  drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
  // empty
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
  for (const NodePtr& child : mChildren)
    child->draw(target, states);
}

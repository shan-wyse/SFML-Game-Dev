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

void SceneNode::checkCollisionPair(SceneNode& node, std::set<Pair>& collisionPair)
{
  if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
    collisionPairs.insert(std::minmax(this, &node));

  for (NodePtr child : mChildren)
    child.checkNodeCollision(node, collisionPairs);
}

void SceneNode::checkSceneCollision(SceneNode& sceneGraph, std::set<Pair>& collisionPairs)
{
  checkNodeCollision(sceneGraph, collisionPairs)

  for (NodePtr child, sceneGraph.mChildren)
    checkSceneCollision(child, collisionPairs);
}

bool SceneNode::isDestroyed() const
{
  return false;
}

bool SceneNode::isMarkedForRemoval() const
{
  return isDestroyed();
}

void SceneNode::removeWrecks()
{
  auto wreckfieldBegin = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));
  mChildren.erase(wreckfieldBegin, mChildren.end());

  std::for_each(mChildren.begin(), mChildren.end(), std::mem_fn(&SceneNode::removeWrecks));
}

bool collision(const SceneNode& a, const SceneNode& b)
{
  return a.getBoundingRect().intersects(b.getBoundingRect());
}

bool matchesCategories(SceneNode::Pair& colliders, Category::Type typeA, Category::Type typeB)
{
  unsigned int categoryA = colliders.first->getCategory();
  unsigned int categoryB = colliders.second->getCategory();

  if (typeA & categoryA && typeB & categoryB)
    return true
  else if (typeA & categoryB && typeB & categoryA) {
    std::swap(colliders.first, colliders.second)
    return true;
  } else
    return false;
}

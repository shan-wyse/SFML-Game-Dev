#include <algorithm>
#include <cmath>
#include <cassert>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "SceneNode.hpp"
#include "Command.hpp"

SceneNode::SceneNode()
: mParent(nullptr)
, mChildren()
, mDefaultCategory(category)
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
  auto foundNode = std::find_if(mChildren.begin(), mChildren.end(), [&] (NodePtr& p) { return p.get() == &node; } );
      // bool { return p.get() == &node; });
  assert (foundNode != mChildren.end());

  NodePtr detachedNode = std::move(*foundNode);
  detachedNode->mParent = nullptr;
  mChildren.erase(foundNode);
  return detachedNode;
}

void SceneNode::update(sf::Time delta, CommandQueue& commands)
{
  updateCurrent(delta, commands);
  updateChildren(delta, commands);
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

void SceneNode::updateChildren(sf::Time delta, CommandQueue& commands)
{
  for (NodePtr& child : mChildren)
    child->update(delta, commands);
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

void SceneNode::checkNodeCollision(SceneNode& node, std::set<Pair>& collisionPair)
{
  if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed())
    collisionPairs.insert(std::minmax(this, &node));

  for (NodePtr child : mChildren)
    child.checkNodeCollision(node, collisionPairs);
}

void SceneNode::drawBoundingRect(sf::RenderTarget& target, sf::RenderStates) const
{
  sf::FloatRect rect = getBoundingRect();

  sf::RectangleShape shape;
  shape.setPosition(sf::Vector2f(rect.left, rect.top));
  shape.setSize(sf::Vector2f(rect.width, rect.height));
  shape.setFillColor(sf::Color::Transparent);
  shape.setOutlineColor(sf::Color::Green);
  shape.setOutlineThickness(1.f);

  target.draw(shape);
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

sf::FloatRect SceneNode::getBoundingRect() const { return sf::FloatRect(); }

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

float distance(const SceneNode& a, const SceneNode& b)
{
  return length(a.getWorldPosition() - b.getWorldPosition());
}

// bool matchesCategories(SceneNode::Pair& colliders, Category::Type typeA, Category::Type typeB)
// {
//   unsigned int categoryA = colliders.first->getCategory();
//   unsigned int categoryB = colliders.second->getCategory();

//   if (typeA & categoryA && typeB & categoryB)
//     return true
//   else if (typeA & categoryB && typeB & categoryA) {
//     std::swap(colliders.first, colliders.second)
//     return true;
//   } else
//     return false;
// }

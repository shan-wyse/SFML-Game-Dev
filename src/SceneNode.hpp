#ifndef SCENE_NODE_HPP
#define SCENE_NODE_HPP

#include <memory>
#include <vector>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

class SceneNode : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
  typedef std::unique_ptr<SceneNode>    NodePtr;
  enum Layer                            { Background, Foreground, LayerCount };

                                        SceneNode();

  void                                  attachChild(NodePtr child);
  NodePtr                               detachChild(const SceneNode& node);

  void                                  update(sf::Time delta);

  sf::Vector2f                          getWorldPosition() const;
  sf::Transform                         getWorldTransform() const;

private:
  virtual void                          updateCurrent(sf::Time delta);
  void                                  updateChildren(sf::Time delta);

  virtual void                          draw(sf::RenderTarget& target, sf::RenderStates states) const final;
  virtual void                          drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
  void                                  drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

  SceneNode*                            mParent;
  std::vector<NodePtr>                  mChildren;
};

#endif // SCENE_NODE_HPP
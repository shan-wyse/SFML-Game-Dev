#ifndef LOADING_STATE_HPP
#define LOADING_STATE_HPP

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "State.hpp"
#include "ParallelTask.hpp"

class LoadingState : public State
{
public:
                          LoadingState(StateStack& stack, Context context);

  virtual bool            processEvent(const sf::Event& event);
  virtual bool            update(sf::Time delta);
  virtual void            render();

  void                    setCompletion(float progress);

private:
  sf::Text                mLoadingText;
  sf::RectangleShape      mProgressBarBackground;
  sf::RectangleShape      mProgressBarFill;
  ParallelTask            mLoadingTask;
};

#endif // LOADING_STATE_HPP

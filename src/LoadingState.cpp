#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp> // remove if not refactoring
#include "LoadingState.hpp"
#include "ResourceManager.hpp"
#include <iostream>

LoadingState::LoadingState(StateStack& stack, Context context)
: State(stack, context)
, mLoadingText()
, mProgressBarBackground()
, mProgressBarFill()
{
  std::cout << "HO";
  mLoadingText.setFont(context.fonts->getResource(Fonts::Id::Main)); // add local variables
  mLoadingText.setString("Loading resources");
  mLoadingText.setOrigin(mLoadingText.getLocalBounds().width / 2.f, mLoadingText.getLocalBounds().height / 2.f);
  mLoadingText.setPosition(context.window->getSize().x / 2u, context.window->getSize().y / 2u + 50); // REFACTOR

  mProgressBarBackground.setFillColor(sf::Color::White);
  mProgressBarBackground.setSize(sf::Vector2f(context.window->getSize().x - 20, 10));
  mProgressBarBackground.setPosition(10, mLoadingText.getPosition().y + 40);

  mProgressBarFill.setFillColor(sf::Color(100, 100, 100));
  mProgressBarFill.setSize(sf::Vector2f(200, 10));
  mProgressBarFill.setPosition(10, mLoadingText.getPosition().y + 40);

  setCompletion(0.f);
  mLoadingTask.launch();
}

bool LoadingState::processEvent(const sf::Event& event)
{
  return true;
}

bool LoadingState::update(sf::Time delta)
{
  if (mLoadingTask.isComplete()) {
    requestStackPop();
    requestStackPush(States::Game);
  } else
    setCompletion(mLoadingTask.getCompletion());

  return true;
}

void LoadingState::render()
{
  sf::RenderWindow& window = *getContext().window;
  window.setView(window.getDefaultView());

  window.draw(mLoadingText);
  window.draw(mProgressBarBackground);
  window.draw(mProgressBarFill);
}

void LoadingState::setCompletion(float progress)
{
  if (progress > 1.f)
    progress = 1.f;

  mProgressBarFill.setSize(sf::Vector2f(mProgressBarBackground.getSize().x * progress, mProgressBarFill.getSize().y));
}

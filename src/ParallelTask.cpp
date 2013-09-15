#include "ParallelTask.hpp"

ParallelTask::ParallelTask()
: mThread(&ParallelTask::launchTask, this)
, mComplete(false)
{
  // empty
}

void ParallelTask::launch()
{
  mComplete = false;
  mElapsedTime.restart();
  mThread.launch();
}

float ParallelTask::getCompletion()
{
  sf::Lock lock(mMutex);
  return mElapsedTime.getElapsedTime().asSeconds() / 1.f;
}

bool ParallelTask::isComplete()
{
  sf::Lock lock(mMutex);
  return mComplete;
}

void ParallelTask::launchTask()
{
  bool ended = false;

  while (!ended) {
    sf::Lock lock(mMutex);
    if (mElapsedTime.getElapsedTime().asSeconds() >= 1.f)
      ended = true;
  }

  { // release lock ASAP
    sf::Lock lock(mMutex);
    mComplete = true;
  }
}

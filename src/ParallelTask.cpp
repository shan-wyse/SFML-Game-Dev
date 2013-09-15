#include "ParallelTask.hpp"

ParallelTask::ParallelTask()
: mThread(&ParallelTask::launchTask, this)
, mFinished(false)
{
  // empty
}

void ParallelTask::launch()
{
  mFinished = false;
  mElapsedTime.restart();
  mThread.launch();
}

float ParallelTask::getCompletion()
{
  sf::Lock lock(mMutex);
  return mElapsedTime.getElapsedTime().asSeconds() / 10.f;
}

bool ParallelTask::isFinished()
{
  sf::Lock lock(mMutex);
  return mFinished;
}

void ParallelTask::launchTask()
{
  bool ended = false;

  while (!ended) {
    sf::Lock lock(mMutex);
    if (mElapsedTime.getElapsedTime().asSeconds() >= 10.f)
      ended = true;
  }

  { // release lock ASAP
    sf::Lock lock(mMutex);
    mFinished = true;
  }
}

#ifndef PARALLEL_TASK_HPP
#define PARALLEL_TASK_HPP

#include <SFML/System/Thread.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Lock.hpp>

class ParallelTask
{
public:
                    ParallelTask();

  void              launch();
  float             getCompletion();
  bool              isComplete();

private:
  void              launchTask();

  sf::Thread        mThread;
  bool              mComplete;
  sf::Clock         mElapsedTime;
  sf::Mutex         mMutex;
};

#endif // PARALLEL_TASK_HPP

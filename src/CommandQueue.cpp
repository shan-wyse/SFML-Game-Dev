#include "CommandQueue.hpp"

void CommandQueue::push(const Command& command)
{
  mQueue.push(command);
}

Command CommandQueue::pop()
{
  mQueue.pop();
}

bool CommandQueue::isEmpty() const
{
  return mQueue.empty();
}

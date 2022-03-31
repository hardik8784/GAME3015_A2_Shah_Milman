#include "CommandQueue.h"
#include "SceneNode.h"

/// <summary>
/// Pushes the new command to the queue
/// </summary>
/// <param name="command"></param>
void CommandQueue::push(const Command& command)
{
	mQueue.push(command);
}

/// <summary>
/// returns the last command from the queue
/// </summary>
/// <returns></returns>
Command CommandQueue::pop()
{
	Command command = mQueue.front();
	mQueue.pop();
	return command;
}

/// <summary>
/// Checks to see if the queue is empty
/// </summary>
/// <returns></returns>
bool CommandQueue::isEmpty() const
{
	return mQueue.empty();
}

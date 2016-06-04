#include "Input/CommandQueue.hpp"

CommandQueue::CommandQueue()
{

}

void CommandQueue::push(const Command &command)
{
	m_queue.push(command);
}

Command CommandQueue::pop()
{
	Command command = m_queue.front();
	m_queue.pop();
	return command;
}

bool CommandQueue::isEmpty() const
{
	return m_queue.empty();
}

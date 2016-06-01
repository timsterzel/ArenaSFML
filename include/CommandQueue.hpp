#ifndef COMMANDQUEUE_HPP
#define COMMANDQUEUE_HPP
#include "Command.hpp"
#include "queue"

class CommandQueue
{
    private:
        std::queue<Command> m_queue;

    public:
        CommandQueue();

        void push(const Command &command);
        Command pop();
        bool isEmpty() const;


};

#endif // COMMANDQUENUE_HPP

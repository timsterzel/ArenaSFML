#ifndef QUEUEHELPER_HPP
#define QUEUEHELPER_HPP
#include <queue>

template <typename T>
class QueueHelper
{
    private:
        std::queue<T> m_queue;

    public:
        QueueHelper();

        void push(const T &value);
        T pop();
        bool isEmpty() const;


};

#include "Input/QueueHelper.inl"

#endif // QUEUEHELPER_HPP

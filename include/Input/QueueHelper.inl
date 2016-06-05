template <typename T>
QueueHelper<T>::QueueHelper()
{

}

template <typename T>
void QueueHelper<T>::push(const T &value)
{
	m_queue.push(value);
}

template <typename T>
T QueueHelper<T>::pop()
{
	T value = m_queue.front();
	m_queue.pop();
	return value;
}

template <typename T>
bool QueueHelper<T>::isEmpty() const
{
	return m_queue.empty();
}

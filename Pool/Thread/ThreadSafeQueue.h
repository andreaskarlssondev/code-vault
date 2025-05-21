#pragma once

#include <queue>
#include <mutex>

template <class T>
class ThreadSafeQueue
{
	public:

		inline void Push(const T& aValue);
		inline const bool TryPop(T& outValue);
		inline const size_t Size() const;

	private:
		std::queue<T> myQueue;
		std::mutex myLock;
};

template<class T>
inline void ThreadSafeQueue<T>::Push(const T& aValue)
{
	myLock.lock();

	myQueue.push(aValue);

	myLock.unlock();
}

template<class T>
inline const bool ThreadSafeQueue<T>::TryPop(T& outValue)
{
	myLock.lock();
	
	if (myQueue.empty())
	{
		myLock.unlock();
		return false;
	}

	outValue = myQueue.front();
	myQueue.pop();

	myLock.unlock();

	return true;
}

template<class T>
inline const size_t ThreadSafeQueue<T>::Size() const
{
	return myQueue.size();
}


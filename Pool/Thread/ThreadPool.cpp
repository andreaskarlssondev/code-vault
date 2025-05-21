#include "ThreadPool.h"

ThreadPool::ThreadPool(const int aNumberOfThreads)
{
	try
	{
		myThreads.reserve(aNumberOfThreads);
		for (int i = 0; i < aNumberOfThreads; ++i)
		{
			myThreads.push_back(std::thread(&ThreadPool::DoWork, this));
		}
	}
	catch (const std::exception& aException)
	{
		myDone = true;
		throw aException;
	}
}

ThreadPool::~ThreadPool()
{
	Terminate();
	Join();
}

void ThreadPool::AddWork(std::function<void()> aFunction)
{
	myWorkQueue.Push(aFunction);
	myConditionalQueueLock.notify_one();
}

void ThreadPool::Terminate()
{
	myDone = true;
	myConditionalQueueLock.notify_all();
}

void ThreadPool::Join()
{
	for (auto& thread : myThreads)
	{
		thread.join();
	}
	myThreads.clear();
}

// should have something that says that there exist a work in the queue before we wake it up
void ThreadPool::DoWork()
{
	while (!myDone)
	{
		std::function<void()> task;
		if (myWorkQueue.TryPop(task))
		{
			task();
		}
		else
		{
			// Wake up
			std::unique_lock<std::mutex> lock(myLock);
			myConditionalQueueLock.wait(lock, [this]() { return myDone || myWorkQueue.Size() != 0; });
		}
	}
}

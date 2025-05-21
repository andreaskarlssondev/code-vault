#pragma once

#include "ThreadSafeQueue.h"

#include <atomic>
#include <thread>
#include <functional>


class ThreadPool
{
	public:
		ThreadPool(const int aNumberOfThreads);
		~ThreadPool();

		void AddWork(std::function<void()> aFunction);

		void Terminate();
		void Join();

		inline const size_t GetQueueSize() const { return myWorkQueue.Size(); }
		inline const size_t Size() const { return myThreads.size(); }

	private:
		void DoWork();

	private:

		std::atomic<bool> myDone;
		std::mutex myLock;
		std::condition_variable myConditionalQueueLock;

		std::vector<std::thread> myThreads;

		ThreadSafeQueue<std::function<void()>> myWorkQueue;


};
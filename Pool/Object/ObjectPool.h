#pragma once

#include <array>
#include <new>
#include <vector>
#include <memory>
#include <assert.h>


template <class T, int Size>
class ObjectPool
{
	// Handles deleting of object outside Pool
	template <class T>
	class ObjectDeleter
	{
	public:
		ObjectDeleter(ObjectPool<T, Size>* aObjectPool) :
			myObjectPool(aObjectPool)
		{
		};

		void operator()(T* aObject) const
		{
			if (myObjectPool) {
				myObjectPool->Recycle(aObject);
			}
		}

	private:
		ObjectPool<T, Size>* myObjectPool;
	};

public:
	ObjectPool();

	// Get a free object
	std::shared_ptr<T> GetObject();

	// Get all free objects;
	const std::vector<T*>& GetFreeObjects() const;

	// Return used object to pool
	void Recycle(T* aObject);

protected:
	std::vector<T*> myFreeObjects;

private:
	char myData[sizeof(T) * Size];
};

template<class T, int Size>
inline ObjectPool<T, Size>::ObjectPool() :
	myData()
{
	for (int i = 0; i < Size; ++i)
	{
		T* ob = new (&myData[i * sizeof(T)]) T();
		myFreeObjects.push_back(ob);
	}
}

template<class T, int Size>
inline std::shared_ptr<T> ObjectPool<T, Size>::GetObject()
{
	assert(myFreeObjects.size() > 0 && L"No free objects in pool");
	T* obj = myFreeObjects.back();
	myFreeObjects.pop_back();

	return {
		obj,
		ObjectDeleter<T>(this)
	};
}

template<class T, int Size>
const inline std::vector<T*>& ObjectPool<T, Size>::GetFreeObjects() const
{
	return myFreeObjects;
}

template<class T, int Size>
inline void ObjectPool<T, Size>::Recycle(T* aObject)
{
	myFreeObjects.push_back(aObject);
}

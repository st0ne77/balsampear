#include "MemoryManager.h"
#include <assert.h>



namespace balsampear
{
	MemoryManager* MemoryManager::sing = nullptr;
	std::mutex MemoryManager::mutex_;
	MemoryManager::MemoryManager() = default;

	MemoryManager::~MemoryManager()
	{
		std::unique_lock<std::mutex> locker(mutex_);
		std::map<Byte*, size_t>::iterator it = sizeCache.begin();
		for (; it != sizeCache.end(); ++it)
		{
			memPool_.deallocate(it->first);
		}
	}

	Byte* MemoryManager::Alloc(size_t size)
	{
		std::unique_lock<std::mutex> locker(mutex_);
		static int count = 0;
		++count;
		Byte* ptr = memPool_.allocate(size);
		sizeCache[ptr] = size;
		return ptr;
	}

	void MemoryManager::Free(Byte * ptr)
	{
		std::unique_lock<std::mutex> locker(mutex_);
		std::map<Byte*, size_t>::iterator it = sizeCache.find(ptr);
		assert(it != sizeCache.end());
		memPool_.deallocate(ptr);
	}

	using namespace std;
	MemoryManager* MemoryManager::getInstance()
	{
		if (!sing)
		{
			std::unique_lock<std::mutex> locker(mutex_);
			if (!sing)
			{
				sing = new MemoryManager();
			}
		}
		return sing;
	}
}




#include "MemoryManager.h"
#include <assert.h>



namespace balsampear
{
	MemoryManager* MemoryManager::sing = nullptr;
	std::mutex MemoryManager::mutex_;
	MemoryManager::MemoryManager() = default;

	MemoryManager::~MemoryManager()
	{
	}

	Byte* MemoryManager::Alloc(size_t size)
	{
		std::unique_lock<std::mutex> locker(mutex_);
		Byte* ptr = memPool_.allocate(size);
		return ptr;
	}

	void MemoryManager::Free(Byte * ptr)
	{
		std::unique_lock<std::mutex> locker(mutex_);
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




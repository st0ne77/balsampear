#pragma once
#include <memory>
#include <mutex>
#include <map>
#include "Base/MemoryPool.h"
//线程安全
using Byte = unsigned char;
namespace balsampear
{
	class MemoryManager
	{
	public:
		
		static MemoryManager* getInstance();
		~MemoryManager();
		Byte* Alloc(size_t size);
		void Free(Byte* ptr);
	private:
		static MemoryManager* sing;
		static std::mutex mutex_;
		MemoryManager();
		MemoryPool<Byte> memPool_;
		std::map<Byte*, size_t> sizeCache;
	};
}



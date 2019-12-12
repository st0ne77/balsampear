#include <mutex>
#include <assert.h>
#include <map>
#include <iostream>
namespace balsampear
{
	template<class T, size_t size = 4096>
	class MemoryPool
	{
	public:
		typedef T*			pointer;

		MemoryPool();
		MemoryPool(const MemoryPool&) = delete;
		MemoryPool& operator=(const MemoryPool&) = delete;
		virtual ~MemoryPool();

		pointer allocate(size_t n = 1);
		void  deallocate(pointer ptr);

	private:
		typedef char* data_pointer_;

		void allocBlock();

		mutable std::mutex lock_;
		data_pointer_ data_;
		std::map<data_pointer_, size_t> busyBlock;
		std::map<data_pointer_, size_t> freeBlock;
		size_t unuse;//debug
	};

	template<class T, size_t size>
	MemoryPool<T, size>::~MemoryPool()
	{
		delete data_;
		data_ = nullptr;
	}

	template<class T, size_t size>
	MemoryPool<T, size>::MemoryPool()
		:data_(nullptr)
	{
		allocBlock();
		unuse = 0;
	}

	template<class T, size_t size>
	void MemoryPool<T, size>::allocBlock()
	{
		if (!data_)
		{
			data_ = reinterpret_cast<data_pointer_>(operator new(size * sizeof(T)));
			assert(data_!=nullptr);
			freeBlock[data_] = size * sizeof(T);
		}
			
	}
	
	template<class T, size_t size>
	typename MemoryPool<T, size>::pointer
	MemoryPool<T, size>::allocate(size_t n)
	{
		std::unique_lock<std::mutex> locker(lock_);
		size_t expectSize = sizeof(T) * n;
		data_pointer_ expectPoint = nullptr;
		std::map<data_pointer_, size_t>::iterator it = freeBlock.begin();
		for (; it != freeBlock.end(); ++it)
		{
			if (it->second >= expectSize)
			{
				expectPoint = it->first;
				break;
			}
		}
		assert(expectPoint != nullptr);
		size_t different = it->second - expectSize;
		freeBlock.erase(it);
		if (different > 0)
		{
			freeBlock[expectPoint + expectSize] = different;
		}
		busyBlock[expectPoint] = expectSize;
		unuse += expectSize;
		std::cout<<"unuse:"<< unuse <<std::endl;
		return reinterpret_cast<pointer>(expectPoint);
	}

	template<class T, size_t size>
	void MemoryPool<T, size>::deallocate(pointer ptr)
	{
		std::unique_lock<std::mutex> locker(lock_);
		data_pointer_ p = reinterpret_cast<data_pointer_>(ptr);
		std::map<data_pointer_, size_t>::iterator current = busyBlock.find(p);
		if (current != busyBlock.end())
		{
			if (unuse <= current->second)
			{
				int i = 0;
			}
			unuse -= current->second;
			std::cout << "unuse:" << unuse << std::endl;
			std::cout << "unuse %:" << (double)unuse / size<< std::endl;

			//find pre free block and next free block to merge it
			std::map<data_pointer_, size_t>::iterator free = freeBlock.begin();
			std::map<data_pointer_, size_t>::iterator free_next;
			for (; free != freeBlock.end(); ++free)
			{
				free_next  = free;
				advance(free_next, 1);// move to next
				if (free->first < current->first && (free_next == freeBlock.end() || free_next->first > current->first))
				{
					break;
				}
			}

			if (free != freeBlock.end())
			{
				//current point + current size equ  next,merge that
				if (free_next != freeBlock.end() && current->first + current->second == free_next->first)
				{
					current->second += free_next->second;
					freeBlock.erase(free_next);
				}

				//pre point + pre size equ current ,merge that
				if (free->first + free->second == current->first)
				{
					free->second += current->second;
				}
				else
				{
					freeBlock[current->first] = current->second;
				}
			}
			else//is first block
			{
				free_next = freeBlock.begin();
				if (free_next != freeBlock.end() && current->first + current->second == free_next->first)
				{
					current->second += free_next->second;
					freeBlock.erase(free_next);
				}
				freeBlock[current->first] = current->second;
			}
			
			busyBlock.erase(current);
		}
	}

}

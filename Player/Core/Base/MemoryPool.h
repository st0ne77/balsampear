#include <mutex>
#include <assert.h>
#include <map>
#include <iostream>

#define print(log)  std::cout<<log<<std::endl;

namespace balsampear
{
	template<class T>
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
		class block
		{
		public:
			block()
			{
				data_ = nullptr;
				size_ = 0;
				pre_ = nullptr;
				next_ = nullptr;
				free_ = false;
			}
			~block()
			{
				delete next_;
				next_ = nullptr;
				if (data_)
				{
					delete[] data_;
					data_ = nullptr;
				}
				
			}
			data_pointer_ data_;
			size_t size_;
			block* pre_;
			block* next_;
			bool free_;
		};
		block* allocBlock(size_t size)
		{
			block* b = new block();
			b->data_ = reinterpret_cast<data_pointer_>(operator new(size));
			assert(b->data_ != nullptr);
			b->size_ = size;
			return b;
		}
		block* head_;
	};

	template<class T>
	MemoryPool<T>::~MemoryPool()
	{
		delete head_;
		head_ = nullptr;
	}

	template<class T>
	MemoryPool<T>::MemoryPool()
		:head_(nullptr)
	{

	}

	
	template<class T>
	typename MemoryPool<T>::pointer
	MemoryPool<T>::allocate(size_t n)
	{
		size_t bytesize = sizeof(T) * n;
		if (head_)
		{
			block* node = head_;
			block* last = nullptr;
			for (; node; node = node->next_)
			{
				last = node;
				if (node->size_ >= bytesize && node->free_)
				{
					node->free_ = false;
					print(0);
					return reinterpret_cast<pointer>(node->data_);
				}
				else if (node->size_ > bytesize && node->free_)
				{
					size_t diff = node->size_ - bytesize;
					node->free_ = false;
					node->size_ = bytesize;

					block* next = new block();
					next->next_ = node->next_;
					next->next_->pre_ = next;
					node->next_ = next;
					next->pre_ = node;
					next->size_ = diff;
					next->data_ = node->data_ + diff;
					next->free_ = true;
					print(1);
					return reinterpret_cast<pointer>(node->data_);
				}
			}
			assert(last != nullptr);
			last->next_ = allocBlock(bytesize);
			last->next_->free_ = false;
			print(2);
			return reinterpret_cast<pointer>(last->next_->data_);
		} 
		else
		{
			head_ = allocBlock(bytesize);
			head_->free_ = false;
			print(3);
			return reinterpret_cast<pointer>(head_->data_);
		}
	}

	template<class T>
	void MemoryPool<T>::deallocate(pointer ptr)
	{
		block* node = head_;
		for (; node; node = node->next_)
		{
			if (reinterpret_cast<pointer>(node->data_) == ptr)
			{
				node->free_ = true;
				break;
			}
		}
	}

}

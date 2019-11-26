#pragma once
#include <mutex>
#include <deque>
namespace PlayerCore
{
	template <typename T, template <typename _Ty, class _Alloc = std::allocator<_Ty> > class Container = std::deque >
	class BlockingQueue
	{
	public:
		BlockingQueue();
		BlockingQueue(int enough, int full);

		virtual ~BlockingQueue() {};


		inline bool isEmpty() const;
		inline bool isEnough() const;
		inline bool isFull() const;

		bool put(const T& t, unsigned long wait_timeout_ms = ULONG_MAX);
		bool tack(T& result, unsigned long wait_timeout_ms = ULONG_MAX);

		void wakeALL()
		{
			cond_full_.wakeAll();
		}

	private:
		mutable std::mutex lock_;//保证能在const方法中上锁
		std::condition_variable cond_empty_;
		std::condition_variable cond_full_;
		Container<T> queue_;
		int enough_;
		int full_;
	};

	template <typename T, template <typename _Ty, typename _Container> class Container>
	BlockingQueue<T, Container>::BlockingQueue()
		:queue_()
		, enough_(40)
		, full_(100)
	{

	}

	template <typename T, template <typename _Ty, typename _Container> class Container>
	BlockingQueue<T, Container>::BlockingQueue(int enough, int full)
		:queue_()
		, enough_(enough)
		, full_(full)
	{

	}

	template <typename T, template <typename _Ty, typename _Container> class Container>
	bool BlockingQueue<T, Container>::isEmpty() const
	{
		std::unique_lock<std::mutex> locker(lock_);
		return queue_.empty();
	}

	template <typename T, template <typename _Ty, typename _Container> class Container>
	bool BlockingQueue<T, Container>::isFull() const
	{
		std::unique_lock<std::mutex> locker(lock_);
		return queue_.size() >= full_;
	}

	template <typename T, template <typename _Ty, typename _Container> class Container>
	bool BlockingQueue<T, Container>::isEnough() const
	{
		std::unique_lock<std::mutex> locker(lock_);
		return queue_.size() >= enough_;
	}

	template <typename T, template <typename _Ty, typename _Container> class Container>
	bool BlockingQueue<T, Container>::put(const T& t, unsigned long wait_timeout_ms /*= ULONG_MAX*/)
	{
		bool ret = true;
		std::unique_lock<std::mutex> locker(lock_);
		if (queue_.size() >= full_)
		{
			cond_full_.wait_for(locker, std::chrono::milliseconds(wait_timeout_ms));//释放锁等待条件满足
		}
		if (queue_.size() >= full_)
		{
			return false;
		}
		queue_.push_back(std::move(t));
		if (queue_.size() >= enough_)
		{
			cond_empty_.notify_all();
		}
		return ret;
	}

	template <typename T, template <typename _Ty, typename _Container> class Container>
	bool BlockingQueue<T, Container>::tack(T& result, unsigned long wait_timeout_ms /*= ULONG_MAX*/)
	{
		bool ret = true;
		std::unique_lock<std::mutex> locker(lock_);
		if (queue_.size() <= 0)
		{
			cond_empty_.wait_for(locker, std::chrono::milliseconds(wait_timeout_ms));
		}

		if (queue_.size() <= 0)
		{
			cond_full_.notify_one();//唤醒等待put的线程
			return false;
		}
		result = std::move(queue_.front());
		queue_.pop_front();
		cond_full_.notify_one();//唤醒等待put的线程
		return ret;
	}


}

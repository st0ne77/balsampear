#include "pch.h"
#include "Base/BlockingQueue.h"
#include "Base/ThreadBase.h"

using namespace balsampear;
typedef BlockingQueue<int> IntQueue;




TEST(BlockingQueueTest, HandleQueue)
{
	IntQueue que;
	ASSERT_TRUE(que.isEmpty());
	ASSERT_FALSE(que.isFull());

	IntQueue que2(2, 5);
	ASSERT_FALSE(que2.isEnough());
	que2.put(1);
	que2.put(2);
	ASSERT_TRUE(que2.isEnough());
	que2.put(3);
	que2.put(4);
	que2.put(5);
	ASSERT_TRUE(que2.isFull());
	int val = 0;
	ASSERT_TRUE(que2.tack(val));
	ASSERT_EQ(1, val);

	class TestThread1 :public balsampear::ThreadBase
	{
	public:
		TestThread1(const StringPiece& name, IntQueue& queue) :ThreadBase(name), queue_(queue){}

		// 通过 ThreadBase 继承
		virtual void run() override
		{
			queue_.put(20);
			queue_.put(20);
			std::cout << "TestThread1 put success"<< std::endl;
		}
		
	private:
		IntQueue &queue_;
	};

	class TestThread2 :public balsampear::ThreadBase
	{
	public:
		TestThread2(const StringPiece& name, IntQueue& queue) :ThreadBase(name), queue_(queue) {}

		// 通过 ThreadBase 继承
		virtual void run() override
		{
			int _val;
			queue_.tack(_val);
			std::cout << "TestThread2 tack success:"<< _val<<std::endl;
		}

	private:
		IntQueue& queue_;
	};
	TestThread1 th1("thread 1", que2);
	TestThread2 th2("thread 2", que2);
	th1.start();
	th2.start();
	th1.join();
	th2.join();
}
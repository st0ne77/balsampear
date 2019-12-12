#include "pch.h"
#include "Base/ThreadBase.h"

using namespace balsampear;
class Thread :public ThreadBase
{
public:
	Thread(const StringPiece& name):ThreadBase(name){}
	virtual void run()
	{
		std::cout << "thread running" << std::endl;
	}

};


TEST(ThreadBaseTest, HandleThread)
{
	Thread th1("thread1");
	th1.start();
	th1.detach();

	Thread th2("thread2");
	th2.start();
	th2.join();
}
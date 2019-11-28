#include "pch.h"
#include "AVThread.h"

using namespace PlayerCore;
TEST(AVThreadTest, handlerun)
{
	AVThread thread("test thread");
	thread.start();

	std::function<void()> task = []()
	{
		std::cout << "task running" << std::endl;
		std::this_thread::sleep_for(std::chrono::microseconds(1000));
	};

	std::cout << "start task" << std::endl;
	thread.startTask(task);
	std::this_thread::sleep_for(std::chrono::microseconds(20000));
	thread.stopTask();
}
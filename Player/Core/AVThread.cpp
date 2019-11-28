#include "AVThread.h"

namespace PlayerCore
{

	AVThread::AVThread(const StringPiece& name)
		:ThreadBase(name),
		pause_(false),
		exit_(false)
	{
		start();
	}

	AVThread::~AVThread()
	{
		exit_ = true;
		join();
	}

	void AVThread::run()
	{
		for (;;)
		{
			if (exit_)
			{
				return;
			}
			if (!task_)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				continue;
			}

			task_();
		}
	}

	void AVThread::startTask(std::function<void()> func)
	{
		task_ = func;
	}

	void AVThread::stopTask()
	{
		task_ = nullptr;
	}

}
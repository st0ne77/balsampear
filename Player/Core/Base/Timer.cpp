#include "Timer.h"


namespace balsampear
{

	Timer::Timer()
		:exit_(false)
	{

	}

	Timer::Timer(std::function<void()> callback)
		:Timer()
	{
		task_ = callback;
	}

	Timer::~Timer()
	{

	}

	void Timer::start(int msec)
	{

		th_ = std::thread([=]()
			{
				for (;;)
				{
					if (this->exit_)
						return;
					std::this_thread::sleep_for(std::chrono::milliseconds(msec));
					if (task_)
						task_();
				}
			});
		th_.detach();
	}

	void Timer::start(int msec, std::function<void()> callback)
	{
		task_ = callback;
		start(msec);
	}

	void Timer::exit()
	{
		exit_ = true;
		th_.join();
	}

}
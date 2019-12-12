#pragma once
#include <functional>
#include <atomic>
#include <thread>
namespace balsampear
{
	class Timer
	{
	public:
		Timer();
		Timer(std::function<void()> callback);
		~Timer();

		void start(int msec);
		void start(int msec, std::function<void()> callback);
		void exit();
	private:
		std::thread th_;
		std::function<void()> task_;
		std::atomic<bool> exit_;
	};
}
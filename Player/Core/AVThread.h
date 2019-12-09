#pragma once
#include "Base/ThreadBase.h"
#include <functional>

namespace balsampear
{
	class AVThread:public ThreadBase
	{
	public:
		AVThread(const StringPiece& name);
		virtual ~AVThread();

		virtual void run();
		void startTask(std::function<void()> func);
		void stopTask();

	private:
		std::function<void()> task_;
		bool pause_;
		bool exit_;
	};
}



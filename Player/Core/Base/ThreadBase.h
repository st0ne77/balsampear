#pragma once
#include <thread>
#include "StringPiece.h"

namespace balsampear
{
	class ThreadBase
	{
	public:
		ThreadBase(const StringPiece& name);
		virtual ~ThreadBase();
		void start();
		void join();
		void detach();//call after start()
		virtual void run() = 0;
		StringPiece getName();
	private:
		void enter();
		void setName(const StringPiece& name);
		explicit ThreadBase(const ThreadBase&) = delete;
		ThreadBase& operator = (const ThreadBase&) = delete;

	private:
		std::thread* thread_;
		StringPiece name_;
	};
}




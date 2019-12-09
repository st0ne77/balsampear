#include "ThreadBase.h"
#include <functional>

namespace balsampear
{
	ThreadBase::ThreadBase(const StringPiece& name)
		:thread_(nullptr),
		name_(name)
	{

	}

	ThreadBase::~ThreadBase()
	{
		delete thread_;
		thread_ = nullptr;
	}

	void ThreadBase::start()
	{
		auto func = std::bind(&ThreadBase::enter, this);
		thread_ = new std::thread(func);
	}

	void ThreadBase::join()
	{
		return thread_->join();
	}

	void ThreadBase::detach()
	{
		return thread_->detach();
	}

	StringPiece ThreadBase::getName()
	{
		return name_;
	}

	void ThreadBase::enter()
	{
		setName(name_);
		this->run();
	}

}



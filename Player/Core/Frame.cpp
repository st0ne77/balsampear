#include "Frame.h"
#include "MemoryManager.h"

namespace balsampear
{

	Frame::Frame()
		:timestamp_msec_(0)
	{

	}

	Frame::~Frame() = default;

	const Byte* Frame::data() const
	{
		if (data_)
		{
			return data_->data();
		}
		return nullptr;
	}

	void Frame::setTimeStampMsec(uint64 t)
	{
		timestamp_msec_ = t;
	}

	uint64 Frame::getTimeStampMsec() const
	{
		return timestamp_msec_;
	}

	void Frame::allocMemory(size_t size)
	{
		if (!data_)
			data_ = std::make_shared<DataManager>();
		data_->allocMemory(size);
	}

	Frame::DataManager::DataManager()
		:d_(nullptr)
	{

	}

	Frame::DataManager::~DataManager()
	{
		if (d_)
			MemoryManager::getInstance()->Free(d_);
	}

	void Frame::DataManager::allocMemory(size_t size)
	{	
		if (d_)
			MemoryManager::getInstance()->Free(d_);
		d_ = MemoryManager::getInstance()->Alloc(size);
	}

	const Byte* Frame::DataManager::data() const
	{
		return d_;
	}

}
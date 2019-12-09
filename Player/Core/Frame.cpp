#include "Frame.h"

namespace balsampear
{
	Frame::Frame()
	{

	}

	Frame::Frame(weak_ptr<Content> content)
	{
		content_ = content.lock();
	}

	Frame::~Frame()
	{

	}

	const Byte* Frame::data() const
	{
		if (content_)
			return &content_->data_[0];
		return nullptr;
	}
}
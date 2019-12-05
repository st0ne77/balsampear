#include "Frame.h"

namespace PlayerCore
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

	vector<Byte> Frame::data() const
	{
		if (content_)
			return content_->data_;
		return vector<Byte>();
	}
}
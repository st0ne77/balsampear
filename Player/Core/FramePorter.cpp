#include "FramePorter.h"

namespace balsampear
{

	FramePorter::FramePorter() = default;

	FramePorter::~FramePorter() = default;

	void FramePorter::updateVideoFrame(std::weak_ptr<VideoFrame> f)
	{
		videoFrameCache_ = f.lock();
	}

	std::shared_ptr<balsampear::VideoFrame> FramePorter::frame()
	{
		return videoFrameCache_;
	}

}
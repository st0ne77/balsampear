#pragma once
#include <memory>
#include "VideoFrame.h"
namespace balsampear
{
	class FramePorter
	{
	public:
		FramePorter();
		~FramePorter();

		void updateVideoFrame(std::weak_ptr<VideoFrame> f);
		std::shared_ptr<VideoFrame> frame();

	private:
		FramePorter(const FramePorter&) = delete;
		FramePorter& operator=(const FramePorter&) = delete;

	protected:
		std::shared_ptr<VideoFrame> videoFrameCache_;
	};
}



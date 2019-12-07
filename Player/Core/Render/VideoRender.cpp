#include "VideoRender.h"
#include <utility>
namespace PlayerCore
{

	VideoRender::VideoRender()
		:frame_ (nullptr)
	{

	}

	VideoRender::~VideoRender()
	{

	}


	void VideoRender::updateFrame(VideoFrame*& frame)
	{
		std::swap(frame_, frame);
	}

	void VideoRender::render()
	{
		
	}

}
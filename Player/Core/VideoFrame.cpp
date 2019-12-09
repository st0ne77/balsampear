#include "VideoFrame.h"


namespace balsampear
{

	VideoFrame::VideoFrame()
		:Frame(),
		width_(0),
		height_(0)
	{

	}

	VideoFrame::VideoFrame(int width, int height, VideoFormat fmt, std::weak_ptr<Frame::Content> content)
		:Frame(content),
		width_(width),
		height_(height),
		format_(fmt)
	{
		
	}

	VideoFrame::~VideoFrame()
	{

	}

	int VideoFrame::width() const
	{
		return width_;
	}

	int VideoFrame::height() const
	{
		return height_;
	}

	VideoFormat VideoFrame::Format() const
	{
		return format_;
	}

	VideoFormat::PixelFormat VideoFrame::pixelFoemat()
	{
		return format_.pixelFormat();
	}

}
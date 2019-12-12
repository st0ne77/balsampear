#include "VideoFrame.h"
extern "C"
{
#include "libavutil/frame.h"
}



namespace balsampear
{

	VideoFrame::VideoFrame()
		:Frame(),
		width_(0),
		height_(0)
	{

	}

	VideoFrame::VideoFrame(AVFrame* avframe)
		:VideoFrame()
	{
		if (avframe)
		{
			width_ = avframe->width;
			height_ = avframe->height;
			fmt_ = VideoFormat(avframe->format);
		}
		
		if (width_ > 0 && height_ > 0)
		{
			size_t size = calcFrameSize();
			allocMemory(size);
			fill(avframe);
		}
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
		return fmt_;
	}

	VideoFormat::PixelFormat VideoFrame::pixelFoemat()
	{
		return fmt_.pixelFormat();
	}

	size_t VideoFrame::calcFrameSize()
	{
		size_t result = 0;
		VideoFormat::PixelFormat pixelfmt = fmt_.pixelFormat();
		
		switch (pixelfmt)
		{
		case balsampear::VideoFormat::PixelFormat::Format_Invalid:
			break;
		case balsampear::VideoFormat::PixelFormat::Format_RGB24:
			result = (size_t)height_ * width_ * 3;
			break;
		case balsampear::VideoFormat::PixelFormat::Format_RGBA32:
			result = (size_t)height_ * width_ * 4;
			break;
		case balsampear::VideoFormat::PixelFormat::Format_YUV420P:
			result = (size_t)height_ * width_ * 3 / 2;
			break;
		case balsampear::VideoFormat::PixelFormat::Format_YUV420:
			result = (size_t)height_ * width_ * 3 / 2;
			break;
		default:
			break;
		}

		return result;
	}

	void VideoFrame::fill(AVFrame* avframe)
	{
		Byte* ptr = (Byte*)data();
		VideoFormat::PixelFormat pixelfmt = fmt_.pixelFormat();

		size_t redSize = (size_t)width_ * height_;
		switch (pixelfmt)
		{
		case balsampear::VideoFormat::PixelFormat::Format_Invalid:
			break;
		case balsampear::VideoFormat::PixelFormat::Format_RGB24:
			//
			break;
		case balsampear::VideoFormat::PixelFormat::Format_RGBA32:
			break;
		case balsampear::VideoFormat::PixelFormat::Format_YUV420P:
			memcpy(ptr, avframe->data[0], redSize);
			memcpy(ptr + redSize, avframe->data[1], redSize / 4);
			memcpy(ptr + redSize * 5 / 4, avframe->data[2], redSize / 4);
			break;
		case balsampear::VideoFormat::PixelFormat::Format_YUV420:
			break;
		default:
			break;
		}
	}

}
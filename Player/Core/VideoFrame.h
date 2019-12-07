#pragma once
#include "Frame.h"
#include "VideoFormat.h"

namespace PlayerCore
{
	class VideoFrame : public Frame
	{
	public:
		VideoFrame();
		VideoFrame(int width, int height, VideoFormat fmt, std::weak_ptr<Frame::Content> content);
		virtual ~VideoFrame();

		int width() const;
		int height() const;
		VideoFormat Format() const;
		VideoFormat::PixelFormat pixelFoemat();
		const Byte* getBuffer() { return &content_->data_[0]; }
	private:
		int width_;
		int height_;
		VideoFormat format_;
	};
}



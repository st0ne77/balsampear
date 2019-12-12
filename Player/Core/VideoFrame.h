#pragma once
#include "Frame.h"
#include "VideoFormat.h"
struct AVFrame;
namespace balsampear
{
	class VideoFrame : public Frame
	{
	public:
		VideoFrame();
		VideoFrame(AVFrame* avframe);
		virtual ~VideoFrame();

		int width() const;
		int height() const;
		VideoFormat Format() const;
		VideoFormat::PixelFormat pixelFoemat();

	protected:
		size_t calcFrameSize();
		void fill(AVFrame* avframe);
	private:
		int width_;
		int height_;
		VideoFormat fmt_;
	};
}



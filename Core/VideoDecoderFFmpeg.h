#pragma once
#include "VideoDecoder.h"
struct AVFrame;
namespace balsampear
{
	class VideoDecoderFFmpeg : public VideoDecoder
	{
	public:
		VideoDecoderFFmpeg();
		virtual ~VideoDecoderFFmpeg();
		virtual bool decode(const Packet& pkt);
		virtual VideoFrame frame();

	protected:
		AVFrame *avframe_;
	};
}


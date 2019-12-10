#pragma once
#include "AudioDecoder.h"
#include "VideoFrame.h"
struct AVFrame;
namespace balsampear
{
	class AudioDeocderFFmpeg :public AudioDecoder
	{
	public:
		AudioDeocderFFmpeg();
		virtual ~AudioDeocderFFmpeg();

		virtual bool decode(const Packet&);
		virtual VideoFrame frame();
	protected:
		AVFrame* avframe_;
	};
}




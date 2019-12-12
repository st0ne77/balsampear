#pragma once
#include "AudioDecoder.h"
struct AVFrame;
namespace balsampear
{
	class AudioDeocderFFmpeg :public AudioDecoder
	{
	public:
		AudioDeocderFFmpeg();
		virtual ~AudioDeocderFFmpeg();

		virtual bool decode(const Packet&);
		virtual AudioFrame frame();
	protected:
		AVFrame* avframe_;
	};
}




#pragma once
#include "VideoDecoder.h"
//#include "VideoFrame.h"
namespace PlayerCore
{
	class VideoDecoderFFmpeg : public VideoDecoder
	{
	public:
		VideoDecoderFFmpeg();
		virtual ~VideoDecoderFFmpeg();
		bool decode(void);
		//virtual VideoFrame frame(void);

	protected:
	private:

	};
}


#include "AVDecoder.h"
extern "C"
{
#include "libavcodec/avcodec.h"
}
namespace balsampear
{
	AVDecoder::AVDecoder()
		:codecCtx_(nullptr),
		codec_(nullptr)
	{
	}

	AVDecoder::~AVDecoder()
	{
		
	}

	void AVDecoder::setCodecContext(AVCodecContext* codecCtx)
	{
		codecCtx_ = codecCtx;
		if (!avcodec_is_open(codecCtx_))
		{
			codec_ = avcodec_find_decoder(codecCtx_->codec_id);
			if (!codec_)
			{
				codecCtx_ = nullptr;
			}
			int ret = avcodec_open2(codecCtx_, codec_, NULL);
			if (ret)
			{
				codecCtx_ = nullptr;
			}
		}

	}

	void AVDecoder::setTimeBase(double tb)
	{
		timebase_ = tb;
	}

}

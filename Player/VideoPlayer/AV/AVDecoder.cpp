#include "stdafx.h"
#include "AVDecoder.h"

extern "C"
{
#include "libavcodec/avcodec.h"
}

AVDecoder::AVDecoder(AVCodecContext* pAVCodecCtx)
	:mpAVCodecCtx(pAVCodecCtx)
{
	AVCodec* pACodec = avcodec_find_decoder(mpAVCodecCtx->codec_id);//根据编码ID找到用于解码的结构体
	if (nullptr != pACodec)
	{
		if (0 == avcodec_open2(mpAVCodecCtx, pACodec, nullptr))
		{
			//initFormater();
		}
	}
}

AVDecoder::~AVDecoder()
{
	avcodec_close(mpAVCodecCtx);
}

bool AVDecoder::putPacket(const Packet& pkt, unsigned long wait_timeout_ms)
{
	return mPktQueue.put(pkt, wait_timeout_ms);
}

Frame AVDecoder::tackFrame()
{
	Frame frame;
	for (; !mFrameQueue.tack(frame, 10);)
	{
		//sleep(1);
	}
	return frame;
}
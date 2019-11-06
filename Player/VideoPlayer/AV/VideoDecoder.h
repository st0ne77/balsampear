#pragma once
#include "AVDecoder.h"

struct SwsContext;
class VideoDecoder : public AVDecoder
{
public:
	VideoDecoder(AVCodecContext* pAVCodecCtx);
	virtual ~VideoDecoder();
	void initFormater();


	virtual void Execute();
protected:
	SwsContext* mpSwsCtx;
	AVFrame* mpFrame;
	AVFrame* mpFrameRGB;
	uint8_t* mpBuffer;
	int mBytes;
};


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

	inline void setTimebase(double _val) { timebase_ = _val; }
protected:
	SwsContext* mpSwsCtx;
	AVFrame* mpFrame;
	AVFrame* mpFrameRGB;
	uint8_t* mpBuffer;
	int mBytes;
	double timebase_;
};


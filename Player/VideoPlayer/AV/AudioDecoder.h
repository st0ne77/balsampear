#pragma once
#include "AVDecoder.h"

struct SwrContext;
class AudioDecoder : public AVDecoder
{
public:
	explicit AudioDecoder(AVCodecContext* pAVCodecCtx);

	void initFormater();

	void Execute();
protected:
	SwrContext* mpSwrCtx;
};


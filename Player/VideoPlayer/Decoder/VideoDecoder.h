#ifndef VIDEODECODER_H 
#define VIDEODECODER_H
#include "AVDecoder.h"

struct AVCodecContext;
struct SwsContext;
struct AVFrame;
class VideoDecoder:public AVDecoder
{
public:
	explicit VideoDecoder(AVCodecContext* pAVCodecCtx);

	virtual ~VideoDecoder();

	virtual bool init();

protected:
	virtual void decode();

private:
	SwsContext *mpSwsCtx;
	AVFrame *mpFrame;
	AVFrame *mpFrameRGB;
	uint8_t *mpBuffer;
	int mBytes;
};
#endif

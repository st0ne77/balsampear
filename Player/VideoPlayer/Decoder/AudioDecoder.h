#ifndef AUDIODECODER_H
#define AUDIODECODER_H
#include "SyncQueue.h"
#include "Packet.h"
#include "AVDecoder.h"

struct AVCodecContext;
struct SwrContext;
class AudioDecoder :public AVDecoder
{
public:
	explicit AudioDecoder(AVCodecContext* pAVCodecCtx);

	virtual ~AudioDecoder();

	virtual bool init();

protected:
	virtual void decode();

private:
	SwrContext* mpSwrCtx;
};


#endif

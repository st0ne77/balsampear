#ifndef AVDECODER
#define AVDECODER
#include <QThread>
#include "SyncQueue.h"
#include "Packet.h"
#include "Frame.h"

struct AVCodecContext;
class AVDecoder:public QThread
{
public:
	AVDecoder(AVCodecContext *pAVCodecCtx);
	virtual ~AVDecoder();

	virtual bool init();

	void addPacket(const Packet& pkt);
	Frame popFrame();

protected:
	virtual void run();
	virtual void decode() = 0;

protected:
	Q_DISABLE_COPY(AVDecoder)
	AVCodecContext* mpAVCodecCtx;
	SyncQueue<Packet> mPktQueue;
	SyncQueue<Frame> mFrameQueue;
};
#endif

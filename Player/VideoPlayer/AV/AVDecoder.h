#pragma once
#include "Task.h"
#include "SyncQueue.h"
#include "Packet.h"
#include "Frame.h"
struct AVCodecContext;
class AVDecoder :public Task
{
public:
	AVDecoder(AVCodecContext* pAVCodecCtx);
	virtual ~AVDecoder();

	bool putPacket(const Packet& pkt, unsigned long wait_timeout_ms = 100);
	Frame tackFrame();

protected:
	AVCodecContext* mpAVCodecCtx;
	SyncQueue<Packet> mPktQueue;
	SyncQueue<Frame> mFrameQueue;
};
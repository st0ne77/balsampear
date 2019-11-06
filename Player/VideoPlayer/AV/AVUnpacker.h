#pragma once
#include "Task.h"
#include "StringPiece.h"

struct AVFormatContext;
class AudioDecoder;
class VideoDecoder;
class AVUnpacker : public Task
{
public:
	AVUnpacker(const String& streamFile);
	virtual ~AVUnpacker();

	void Execute();
	inline AudioDecoder* getADecoder() { return pADecoder; }
	inline VideoDecoder* getVDecoder() { return pVDecoder; }
private:
	void init();
	void findDecoder();

private:
	String file_;
	AVFormatContext* mpFormatCtx;
	int AStreamIndex;
	int VStreamIndex;
	AudioDecoder* pADecoder;
	VideoDecoder* pVDecoder;
};
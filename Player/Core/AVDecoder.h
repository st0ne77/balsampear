#pragma once

struct AVCodecContext;
class AVDecoder
{
public:
	AVDecoder();
	virtual ~AVDecoder();
	virtual bool decode(void) = 0;
	void setCodecContext(AVCodecContext* codecCtx);

protected:
	AVCodecContext* codecCtx_;	
};


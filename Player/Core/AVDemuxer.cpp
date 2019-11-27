#include "AVDemuxer.h"

namespace PlayerCore
{
	AVDemuxer::AVDemuxer()
		:formatCtx_(nullptr)
	{

	}

	AVDemuxer::~AVDemuxer()
	{

	}

	void AVDemuxer::setFormatContext(AVFormatContext* ctx)
	{
		formatCtx_ = ctx;
	}
}


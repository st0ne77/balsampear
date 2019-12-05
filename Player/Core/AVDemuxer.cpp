# pragma warning (disable:4819)
#include "AVDemuxer.h"
extern "C"
{
#include "libavformat/avformat.h"
}


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

	bool AVDemuxer::readFrame()
	{
		bool result = false;
		AVPacket pkt;
		av_init_packet(&pkt);
		if (av_read_frame(formatCtx_, &pkt) >= 0)
		{
			pkt_ = Packet::createFromAVPacket(&pkt);
			result = true;
		}
		av_packet_unref(&pkt);
		return result;
	}

	Packet AVDemuxer::packet()
	{
		return pkt_;
	}

}


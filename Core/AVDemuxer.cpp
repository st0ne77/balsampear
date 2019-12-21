# pragma warning (disable:4819)
#include "AVDemuxer.h"
extern "C"
{
#include "libavformat/avformat.h"
}
#include <assert.h>

namespace balsampear
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

	void AVDemuxer::seek(double sec)
	{
		uint64 seekTag = sec * AV_TIME_BASE;
		int ret = avformat_seek_file(formatCtx_, -1, INT64_MIN, seekTag, INT64_MAX, 0);
		assert(ret >= 0);
	}

	bool AVDemuxer::readFrame()
	{
		bool result = false;
		AVPacket pkt;
		av_init_packet(&pkt);
		int ret = av_read_frame(formatCtx_, &pkt);
		if (ret >= 0)
		{
			pkt_ = Packet::createFromAVPacket(&pkt);
			result = true;
		}
		else
		{
			int eof = AVERROR_EOF;
			if (ret == eof)
			{
				pkt_ = Packet::createEofPacket();
				result = true;
			}
		}
		av_packet_unref(&pkt);
		return result;
	}

	Packet AVDemuxer::packet()
	{
		return pkt_;
	}

}


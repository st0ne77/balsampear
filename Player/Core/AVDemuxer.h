#pragma once
#include "Packet.h"

struct AVFormatContext;
namespace balsampear
{
	class AVDemuxer
	{
	public:
		AVDemuxer();
		virtual ~AVDemuxer();
		void setFormatContext(AVFormatContext* ctx);
		bool readFrame();
		Packet packet();
		bool atEnd();

	private:
		AVFormatContext* formatCtx_;
		Packet pkt_;
	};
}



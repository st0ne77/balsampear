#pragma once
#include "Packet.h"

struct AVFormatContext;
using uint64 = unsigned long long;
namespace balsampear
{
	class AVDemuxer
	{
	public:
		AVDemuxer();
		virtual ~AVDemuxer();
		void setFormatContext(AVFormatContext* ctx);
		void seek(double sec);
		bool readFrame();
		Packet packet();

	private:
		AVFormatContext* formatCtx_;
		Packet pkt_;
	};
}



#pragma once
struct AVFormatContext;
namespace PlayerCore
{
	class AVDemuxer
	{
	public:
		AVDemuxer();
		virtual ~AVDemuxer();
		void setFormatContext(AVFormatContext* ctx);

	private:
		AVFormatContext* formatCtx_;
	};
}



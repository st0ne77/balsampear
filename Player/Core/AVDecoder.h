#pragma once

struct AVCodecContext;
struct AVCodec;
namespace PlayerCore
{
	class Packet;
	class AVDecoder
	{
	public:
		AVDecoder();
		virtual ~AVDecoder();
		virtual bool decode(const Packet& pkt) = 0;
		void setCodecContext(AVCodecContext* codecCtx);

	protected:
		AVCodecContext* codecCtx_;
		AVCodec *codec_;
	};
}



#pragma once
extern "C"
{
#include "libavcodec/avcodec.h"
}

#pragma warning(disable: 4819)
namespace balsampear
{
	class Packet
	{
	public:
		Packet();
		Packet(const Packet& other);
		Packet& operator=(const Packet& other);
		~Packet();
		static Packet createFromAVPacket(const AVPacket* avpkt);
		const AVPacket* asAVPacket() const;
		static Packet pktEof;
		static Packet createEofPacket();

		void setEof(bool _val);
		bool eof();
	private:
		AVPacket avpkt;
		bool eof_;
	};
}



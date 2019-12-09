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

	private:
		AVPacket avpkt;
	};
}



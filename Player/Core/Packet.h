#pragma once
extern "C"
{
#include "libavcodec/avcodec.h"
}

#pragma warning(disable: 4819)
namespace PlayerCore
{
	class Packet
	{
	public:
		Packet();
		Packet(const Packet& other);
		Packet& operator=(const Packet& other);
		~Packet();
		static Packet createFromAVPacket(const AVPacket* avpkt);
		const AVPacket* asAVPacket();

	private:
		AVPacket avpkt;
	};
}



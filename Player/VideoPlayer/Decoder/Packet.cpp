#include "stdafx.h"
#include "Packet.h"
extern "C"
{
#include "libavcodec/avcodec.h"
}


Packet::Packet(const AVPacket& pkt)
	:mpPacket(nullptr)
{
	mpPacket = av_packet_clone((AVPacket*)&pkt);
}

Packet::Packet(const Packet& other)
{
	if (this != &other)
	{
		mpPacket = av_packet_clone(other.mpPacket);
	}
}

Packet::Packet()
	:mpPacket(nullptr)
{

}

Packet::~Packet()
{
	av_packet_free(&mpPacket);
}

Packet& Packet::operator=(const Packet& other)
{
	if (this != &other)
	{
		if (mpPacket)
		{
			av_packet_free(&mpPacket);
		}
		mpPacket = av_packet_clone(other.mpPacket);
	}
	return *this;
}

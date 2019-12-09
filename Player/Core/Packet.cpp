# pragma warning (disable:4819)
#include "Packet.h"

namespace balsampear
{
	Packet::Packet()
	{
		av_init_packet(&avpkt);
	}

	Packet::Packet(const Packet& other)
	{
		av_init_packet(&avpkt);
		av_packet_ref(&avpkt, &other.avpkt);
	}

	Packet& Packet::operator=(const Packet& other)
	{
		av_init_packet(&avpkt);
		av_packet_ref(&avpkt, &other.avpkt);
		return *this;
	}

	balsampear::Packet::~Packet()
	{
		av_packet_unref(&avpkt);
	}

	Packet Packet::createFromAVPacket(const AVPacket* avpkt)
	{
		Packet pkt;
		av_packet_ref(&pkt.avpkt, avpkt);
		return pkt;
	}

	const AVPacket* Packet::asAVPacket() const
	{
		return (const AVPacket*)&avpkt;
	}
}
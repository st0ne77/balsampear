# pragma warning (disable:4819)
#include "Packet.h"

namespace balsampear
{
	Packet::Packet()
	{
		av_init_packet(&avpkt);
		eof_ = false;
	}

	Packet::Packet(const Packet& other)
	{
		av_init_packet(&avpkt);
		av_packet_ref(&avpkt, &other.avpkt);
		eof_ = other.eof_;
	}

	Packet& Packet::operator=(const Packet& other)
	{
		av_init_packet(&avpkt);
		av_packet_ref(&avpkt, &other.avpkt);
		eof_ = other.eof_;
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

	Packet Packet::pktEof = createEofPacket();

	Packet Packet::createEofPacket()
	{
		Packet pkt;
		pkt.setEof(true);
		return pkt;
	}

	void Packet::setEof(bool _val)
	{
		eof_ = _val;
	}

	bool Packet::eof()
	{
		return eof_;
	}

}
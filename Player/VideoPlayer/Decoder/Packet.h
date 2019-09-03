

#ifndef PACKET_H
#define PACKET_H

struct AVPacket;
class Packet
{
public:
	explicit Packet();
	explicit Packet(const AVPacket& pkt);
	Packet(const Packet& other);

	virtual ~Packet();

	Packet& operator=(const Packet& other);

	inline AVPacket* getPacket()
	{
		return mpPacket;
	}

private:
	AVPacket* mpPacket;
};

#endif
#pragma once
#include "AudioDecoder.h"

namespace balsampear
{
	class AudioDeocderFFmpeg :public AudioDecoder
	{
	public:
		AudioDeocderFFmpeg();
		virtual ~AudioDeocderFFmpeg();

		virtual bool decode(const Packet&);
		
	protected:
	};
}




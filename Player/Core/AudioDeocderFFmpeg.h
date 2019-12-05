#pragma once
#include "AudioDecoder.h"

namespace PlayerCore
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




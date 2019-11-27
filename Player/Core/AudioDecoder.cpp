#include "AudioDecoder.h"
#include "Base/StringPiece.h"
#include "AudioDeocderFFmpeg.h"
namespace PlayerCore
{
	AudioDecoder::AudioDecoder()
	{

	}

	AudioDecoder::~AudioDecoder()
	{

	}

	shared_ptr<AudioDecoder> AudioDecoder::create(const StringPiece& name)
	{
		shared_ptr<AudioDecoder> decoder;
		if (name == "ffmpeg")
		{
			decoder = shared_ptr<AudioDecoder>(new AudioDeocderFFmpeg());
		}
		return decoder;
	}
}


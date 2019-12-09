#include "AudioDecoder.h"
#include "Base/StringPiece.h"
#include "AudioDeocderFFmpeg.h"
namespace balsampear
{
	AudioDecoder::AudioDecoder()
	{

	}

	AudioDecoder::~AudioDecoder()
	{

	}

	unique_ptr<AudioDecoder> AudioDecoder::create(const StringPiece& name)
	{
		unique_ptr<AudioDecoder> decoder;
		if (name == "ffmpeg")
		{
			decoder = std::make_unique<AudioDeocderFFmpeg>();
		}
		return decoder;
	}
}


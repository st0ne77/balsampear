#include "VideoDecoder.h"
#include "VideoDecoderFFmpeg.h"
using std::vector;
namespace PlayerCore
{
	VideoDecoder::VideoDecoder()
	{

	}

	VideoDecoder::~VideoDecoder()
	{

	}

	unique_ptr<VideoDecoder> VideoDecoder::create(const StringPiece& name /*= "ffmpeg"*/)
	{
		unique_ptr<VideoDecoder> decoder;
		if (name == "ffmpeg")
		{
			decoder = std::make_unique<VideoDecoderFFmpeg>();
		}
		return decoder;
	}
}


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

	std::shared_ptr<VideoDecoder> VideoDecoder::create(const StringPiece& name /*= "ffmpeg"*/)
	{
		std::shared_ptr<VideoDecoder> decoder;
		if (name == "ffmpeg")
		{
			decoder = std::shared_ptr<VideoDecoder>( new VideoDecoderFFmpeg());
		}
		return decoder;
	}
}


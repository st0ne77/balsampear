#pragma once
#include "AVDecoder.h"
#include "Base/StringPiece.h"
#include <memory>
#include "VideoFrame.h"
using std::unique_ptr;
namespace PlayerCore
{
	class VideoDecoder : public AVDecoder
	{
	public:
		VideoDecoder();
		virtual ~VideoDecoder();
		virtual VideoFrame frame(void) = 0;


		static unique_ptr<VideoDecoder> create(const StringPiece& name = "ffmpeg");
	protected:

	private:
		
	};
}

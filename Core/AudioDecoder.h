#pragma once
#include "AVDecoder.h"
#include <memory>
#include "Base/StringPiece.h"
#include "AudioFrame.h"

using std::unique_ptr;
namespace balsampear
{
	class AudioDecoder :public AVDecoder
	{
	public:
		AudioDecoder();
		virtual ~AudioDecoder();
		virtual AudioFrame frame() = 0;
		static unique_ptr<AudioDecoder> create(const StringPiece& name = "ffmpeg");
	protected:
	};
}



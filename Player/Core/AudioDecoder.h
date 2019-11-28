#pragma once
#include "AVDecoder.h"
#include <memory>
#include "Base/StringPiece.h"

using std::unique_ptr;
namespace PlayerCore
{
	class AudioDecoder :public AVDecoder
	{
	public:
		AudioDecoder();
		virtual ~AudioDecoder();
		virtual bool decode(void) = 0;

		static unique_ptr<AudioDecoder> create(const StringPiece& name = "ffmpeg");
	protected:
	};
}



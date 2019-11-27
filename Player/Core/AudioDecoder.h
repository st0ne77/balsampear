#pragma once
#include "AVDecoder.h"
#include <memory>
#include "Base/StringPiece.h"

using std::shared_ptr;
namespace PlayerCore
{
	class AudioDecoder :public AVDecoder
	{
	public:
		AudioDecoder();
		virtual ~AudioDecoder();
		virtual bool decode(void) = 0;

		static shared_ptr<AudioDecoder> create(const StringPiece& name = "ffmpeg");
	protected:
	};
}



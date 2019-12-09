#pragma once
#include "AVDecoder.h"
#include <memory>
#include "Base/StringPiece.h"

using std::unique_ptr;
namespace balsampear
{
	class AudioDecoder :public AVDecoder
	{
	public:
		AudioDecoder();
		virtual ~AudioDecoder();

		static unique_ptr<AudioDecoder> create(const StringPiece& name = "ffmpeg");
	protected:
	};
}



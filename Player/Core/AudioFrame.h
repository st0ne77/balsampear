#pragma once
#include "Frame.h"
#include "AudioFormat.h"

struct AVFrame;
namespace balsampear
{
	class AudioFrame :
		public Frame
	{
	public:
		AudioFrame();
		explicit AudioFrame(AudioFormat fmt,AVFrame* avframe = nullptr);
		virtual ~AudioFrame();

		AudioFormat format();
		int sampleNumPerChannel() const;

		void fill(AVFrame* avframe, size_t size);
	protected:
		size_t calcFrameSize();
		
	protected:
		AudioFormat fmt_;
		int sampleNumPerChannel_;
	};
}



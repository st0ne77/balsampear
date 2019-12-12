#include "AudioFrame.h"
#include "libavutil/frame.h"


namespace balsampear
{
	AudioFrame::AudioFrame()
		:Frame(),
		fmt_(),
		sampleNumPerChannel_(0)
	{

	}

	AudioFrame::AudioFrame(AudioFormat fmt, AVFrame* avframe)
		:AudioFrame()
	{
		fmt_ = fmt;
		if (avframe)
		{
			sampleNumPerChannel_ = avframe->nb_samples;
		}
	}

	

	AudioFrame::~AudioFrame()
	{

	}

	balsampear::AudioFormat AudioFrame::format()
	{
		return fmt_;
	}

	int AudioFrame::sampleNumPerChannel() const
	{
		return sampleNumPerChannel_;
	}

	size_t AudioFrame::calcFrameSize()
	{
		AudioFormat::SampleFormat samplefmt = fmt_.sampleFormat();
		size_t result = 0;
		switch (samplefmt)
		{
		case balsampear::AudioFormat::SampleFormat::SampleFormat_Invalid:
			break;
		case balsampear::AudioFormat::SampleFormat::SampleFormat_Unsigned8:
			result = 1;
			break;
		case balsampear::AudioFormat::SampleFormat::SampleFormat_Signed16:
			result = 2;
			break;
		case balsampear::AudioFormat::SampleFormat::SampleFormat_Signed32:
			result = 4;
			break;
		case balsampear::AudioFormat::SampleFormat::SampleFormat_Float:
			result = 4;
			break;
		case balsampear::AudioFormat::SampleFormat::SampleFormat_Double:
			result = 8;
			break;
		default:
			break;
		}

		AudioFormat::ChannelLayout layout = fmt_.channelLayout();
		switch (layout)
		{
		case balsampear::AudioFormat::ChannelLayout::ChannelLayout_Invalid:
			result *= 0;
			break;
		case balsampear::AudioFormat::ChannelLayout::ChannelLayout_Mono:
			result *= 1;
			break;
		case balsampear::AudioFormat::ChannelLayout::ChannelLayout_Stereo:
			result *= 2;
			break;
		default:
			break;
		}

		return result *= sampleNumPerChannel_;
	}

	void AudioFrame::fill(AVFrame* avframe, size_t size)
	{
		Byte* ptr = (Byte*)data();
		AudioFormat::SampleFormat samplefmt = fmt_.sampleFormat();
		
		switch (samplefmt)
		{
		case balsampear::AudioFormat::SampleFormat::SampleFormat_Invalid:
		case balsampear::AudioFormat::SampleFormat::SampleFormat_Unsigned8:
		case balsampear::AudioFormat::SampleFormat::SampleFormat_Signed16:
		case balsampear::AudioFormat::SampleFormat::SampleFormat_Signed32:
		case balsampear::AudioFormat::SampleFormat::SampleFormat_Float:
		case balsampear::AudioFormat::SampleFormat::SampleFormat_Double:
			memcpy(ptr, avframe->data[0], size);
		default:
			break;
		}
	}

}
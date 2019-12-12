#include "AudioFormat.h"
extern "C"
{
#include "libavutil/samplefmt.h"
#include "libavutil/channel_layout.h"
}
#include <map>


using std::map;
namespace balsampear
{
	static const map<AudioFormat::SampleFormat, int> samplefmt_map =
	{
		{AudioFormat::SampleFormat::SampleFormat_Unsigned8,	AV_SAMPLE_FMT_U8},
		{AudioFormat::SampleFormat::SampleFormat_Signed16,	AV_SAMPLE_FMT_S16},
		{AudioFormat::SampleFormat::SampleFormat_Signed32,	AV_SAMPLE_FMT_S32},
		{AudioFormat::SampleFormat::SampleFormat_Float,	AV_SAMPLE_FMT_FLT},
		{AudioFormat::SampleFormat::SampleFormat_Double,	AV_SAMPLE_FMT_DBL}
	};

	static const map<AudioFormat::ChannelLayout, int> channel_layout_map =
	{
		{AudioFormat::ChannelLayout::ChannelLayout_Mono, AV_CH_LAYOUT_MONO},
		{AudioFormat::ChannelLayout::ChannelLayout_Stereo, AV_CH_LAYOUT_STEREO},
	};

	AudioFormat::AudioFormat()
		:sample_fmt_(SampleFormat::SampleFormat_Invalid),
		sample_fmt_ff_(AV_SAMPLE_FMT_NONE),
		channel_layout_(ChannelLayout::ChannelLayout_Invalid),
		channel_layout_ff_(0),
		sample_rate_(0)
	{

	}

	AudioFormat::~AudioFormat()
	{

	}

	AudioFormat::SampleFormat AudioFormat::sampleFormatFromFFmpeg(int fffmt)
	{
		map<AudioFormat::SampleFormat, int>::const_iterator it = samplefmt_map.begin();
		for (;it!=samplefmt_map.end();++it)
		{
			if (it->second == fffmt)
			{
				return it->first;
			}
		}
		return AudioFormat::SampleFormat::SampleFormat_Invalid;
	}

	int AudioFormat::sampleFormatToFFmpeg(SampleFormat fmt)
	{
		map<AudioFormat::SampleFormat, int>::const_iterator it = samplefmt_map.find(fmt);
		if (it != samplefmt_map.end())
		{
			return it->second;
		}
		return AV_SAMPLE_FMT_NONE;
	}

	balsampear::AudioFormat::ChannelLayout AudioFormat::channelLayoutFromFFmpeg(int layout_ff)
	{
		map<AudioFormat::ChannelLayout, int>::const_iterator it = channel_layout_map.begin();
		for (; it != channel_layout_map.end(); ++it)
		{
			if (it->second == layout_ff)
			{
				return it->first;
			}
		}
		return AudioFormat::ChannelLayout::ChannelLayout_Invalid;
	}

	int AudioFormat::channelLayoutToFFmpeg(ChannelLayout layout)
	{
		map<AudioFormat::ChannelLayout, int>::const_iterator it = channel_layout_map.find(layout);
		if (it != channel_layout_map.end())
		{
			return it->second;
		}
		return 0;
	}

	AudioFormat AudioFormat::create(int sample_fmt_ff, int channel_layout_ff, int sample_rate)
	{
		AudioFormat obj;
		obj.setSampleFormatFFmpeg(sample_fmt_ff);
		return obj;
	}

	void AudioFormat::setSampleFormatFFmpeg(int sample_fmt_ff)
	{
		sample_fmt_ff_ = sample_fmt_ff;
		sample_fmt_ = sampleFormatFromFFmpeg(sample_fmt_ff);
	}

	void AudioFormat::setSampleFormat(SampleFormat sample_fmt)
	{
		sample_fmt_ = sample_fmt;
		sample_fmt_ff_ = sampleFormatToFFmpeg(sample_fmt);
	}

	balsampear::AudioFormat::SampleFormat AudioFormat::sampleFormat()
	{
		return sample_fmt_;
	}

	void AudioFormat::setChannelLayoutFFmpeg(int channel_layout_ff)
	{
		channel_layout_ff_ = channel_layout_ff;
		channel_layout_ = channelLayoutFromFFmpeg(channel_layout_ff);
	}

	void AudioFormat::setChannelLayout(ChannelLayout channel_layout)
	{
		channel_layout_ = channel_layout;
		channel_layout_ff_ = channelLayoutToFFmpeg(channel_layout);
	}

	balsampear::AudioFormat::ChannelLayout AudioFormat::channelLayout()
	{
		return channel_layout_;
	}

	void AudioFormat::setSampleRate(int rate)
	{
		sample_rate_ = rate;
	}

	int AudioFormat::sampleRate()
	{
		return sample_rate_;
	}

	

}
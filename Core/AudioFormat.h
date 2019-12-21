#pragma once

namespace balsampear
{
	class AudioFormat
	{
	public:
		enum class SampleFormat:int
		{
			SampleFormat_Invalid = -1,
			SampleFormat_Unsigned8,
			SampleFormat_Signed16,
			SampleFormat_Signed32,
			SampleFormat_Float,
			SampleFormat_Double,
		};
		enum class ChannelLayout :int
		{
			ChannelLayout_Invalid = -1,
			ChannelLayout_Mono,
			ChannelLayout_Stereo
		};

		AudioFormat();
		virtual ~AudioFormat();

		static SampleFormat sampleFormatFromFFmpeg(int fffmt);
		static int sampleFormatToFFmpeg(SampleFormat fmt);
		static ChannelLayout channelLayoutFromFFmpeg(int layout_ff);
		static int channelLayoutToFFmpeg(ChannelLayout layout);

		static AudioFormat create(int sample_fmt_ff, int channel_layout_ff, int sample_rate);

		void setSampleFormatFFmpeg(int sample_fmt_ff);
		void setSampleFormat(SampleFormat sample_fmt);
		SampleFormat sampleFormat();
		void setChannelLayoutFFmpeg(int channel_layout_ff);
		void setChannelLayout(ChannelLayout channel_layout);
		ChannelLayout channelLayout();
		void setSampleRate(int rate);
		int sampleRate();

	protected:
		SampleFormat sample_fmt_;
		int sample_fmt_ff_;
		ChannelLayout channel_layout_;
		int channel_layout_ff_;
		int sample_rate_;
	};
}



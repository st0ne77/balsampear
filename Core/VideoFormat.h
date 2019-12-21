#pragma once

using uint = unsigned int;
namespace balsampear
{
	class VideoFormat
	{
	public:
		enum class PixelFormat :int
		{
			Format_Invalid = -1,
			Format_RGB24,
			Format_RGBA32,
			Format_YUV420P,
			Format_YUV420,
		};
		VideoFormat();
		explicit VideoFormat(PixelFormat fmt);
		explicit VideoFormat(int fmt_ff);

		static PixelFormat pixelFormatFromFFmpeg(int fmt_ff);
		static int FFmpegFormatFromPixel(PixelFormat fmt);
		PixelFormat pixelFormat() const;
		uint calcFrameByteSize(int width, int height);
	private:
		PixelFormat fmt_;
		int fixfmt_ff_;//pixel format for ffmpeg
	};
}



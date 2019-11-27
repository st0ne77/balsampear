#pragma once


#pragma warning(disable: 26812)
class VideoFormat
{
public:
	enum class PixelFormat:int 
	{ 
		Format_Invalid = -1, 
		Format_RGB24,
		Format_YUV420P,
	};
	VideoFormat();
	VideoFormat(PixelFormat fmt);
	VideoFormat(int fmt_ff);

	PixelFormat pixelFormatFromFFmpeg(int fmt_ff);
	int FFmpegFormatFromPixel(PixelFormat fmt);
private:
	PixelFormat fmt_;
	int fixfmt_ff_;//pixel format for ffmpeg
};


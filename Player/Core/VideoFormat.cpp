#include "VideoFormat.h"
#include <map>
extern "C"
{
#include "libavutil/pixfmt.h"
}
using std::map;
static const map<VideoFormat::PixelFormat, int> pixfmt_map =
{
	{VideoFormat::PixelFormat::Format_RGB24,	AV_PIX_FMT_RGB24},
	{VideoFormat::PixelFormat::Format_YUV420P,	AV_PIX_FMT_YUV420P}
};

VideoFormat::VideoFormat()
	:fmt_(PixelFormat::Format_Invalid),
	fixfmt_ff_(AV_PIX_FMT_NONE)
{

}

VideoFormat::VideoFormat(PixelFormat fmt)
	:fmt_(fmt)
{
	fixfmt_ff_ = FFmpegFormatFromPixel(fmt);
}


VideoFormat::VideoFormat(int fmt_ff)
	:fixfmt_ff_(fmt_ff)
{
	fmt_ = pixelFormatFromFFmpeg(fmt_ff);
}

VideoFormat::PixelFormat VideoFormat::pixelFormatFromFFmpeg(int fmt_ff)
{
	std::map<VideoFormat::PixelFormat, int>::const_iterator it = pixfmt_map.begin();
	for (;it != pixfmt_map.end(); ++it)
	{
		if (it->second == fmt_ff)
		{
			return it->first;
		}
	}
	return PixelFormat::Format_Invalid;
}

int VideoFormat::FFmpegFormatFromPixel(PixelFormat fmt)
{
	std::map<VideoFormat::PixelFormat, int>::const_iterator it = pixfmt_map.find(fmt);
	if (pixfmt_map.end() != it)
	{
		return it->second;
	}
	return AV_PIX_FMT_NONE;
}
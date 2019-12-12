#include "VideoFormat.h"
#include <map>
extern "C"
{
#include "libavutil/pixfmt.h"
}
using std::map;
namespace balsampear
{

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
		for (; it != pixfmt_map.end(); ++it)
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

	VideoFormat::PixelFormat VideoFormat::pixelFormat() const
	{
		return fmt_;
	}

	uint VideoFormat::calcFrameByteSize(int width, int height)
	{
		uint result = 0;
		switch (fmt_)
		{
		case VideoFormat::PixelFormat::Format_Invalid:
			break;
		case VideoFormat::PixelFormat::Format_RGB24:
			result = width * height * 3;
			break;
		case VideoFormat::PixelFormat::Format_RGBA32:
			result = width * height * 4;
			break;
		case VideoFormat::PixelFormat::Format_YUV420P:
		case VideoFormat::PixelFormat::Format_YUV420:
			result = width * height * 3 / 2;
			break;
		default:
			break;
		}
		return result;
	}
}
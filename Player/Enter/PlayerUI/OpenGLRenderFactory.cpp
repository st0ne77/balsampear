#include "OpenGLRenderFactory.h"
#include "OpenGLYUV420PRender.h"

namespace PlayerCore
{

	unique_ptr<PlayerCore::VideoRender> OpenGLRenderFactory::create(VideoFormat::PixelFormat format)
	{
		unique_ptr<VideoRender> result;
		switch (format)
		{
		case VideoFormat::PixelFormat::Format_RGB24:
			break;
		case VideoFormat::PixelFormat::Format_YUV420P:
			result = std::make_unique<OpenGLYUV420PRender>();
			break;
		default:
			break;
		}
		return result;
	}

}
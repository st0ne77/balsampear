#include "VideoRenderFactory.h"
#include "OpenGLRenderFactory.h"

namespace PlayerCore
{
	unique_ptr<VideoRender> VideoRenderFactory::create(VideoRenderType type, VideoFormat::PixelFormat format)
	{
		unique_ptr<VideoRender> result;
		switch (type)
		{
		case VideoRenderType::Render_OpenGL:
			result = OpenGLRenderFactory::create(format);
			break;
		default:
			break;
		}
		return result;
	}

}
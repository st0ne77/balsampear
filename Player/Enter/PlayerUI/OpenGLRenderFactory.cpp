#include "OpenGLRenderFactory.h"
#include "OpenGLYUV420PRenderer.h"

namespace balsampear
{
	std::shared_ptr<OpenGLRenderer> OpenGLRenderFactory::create(VideoFormat::PixelFormat fmt)
	{
		std::shared_ptr<OpenGLRenderer> result;

		switch (fmt)
		{
		case VideoFormat::PixelFormat::Format_Invalid:
			break;
		case VideoFormat::PixelFormat::Format_RGB24:
			break;
		case VideoFormat::PixelFormat::Format_YUV420P:
			result = std::make_shared<OpenGLYUV420PRender>();
			break;
		default:
			break;
		}
		if (result)
		{
			result->createVertex();
			result->createTexture();
			result->createSahder();
		}
		return result;
	}

}
#pragma once
#include "VideoFormat.h"
#include <memory>
#include "VideoRender.h"

using std::unique_ptr;
namespace PlayerCore
{
	class OpenGLRenderFactory
	{
	public:
		static unique_ptr<VideoRender> create(VideoFormat::PixelFormat format);
	};
}
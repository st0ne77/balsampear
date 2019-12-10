#pragma once
#include "VideoFormat.h"
#include <memory>
#include "OpenGLRenderer.h"

namespace balsampear
{
	class OpenGLRenderFactory
	{
	public:
		static std::shared_ptr<OpenGLRenderer> create(VideoFormat::PixelFormat fmt);
		
	};
}
#pragma once
#include "VideoFormat.h"
#include <memory>
#include "VideoRender.h"

using std::unique_ptr;
namespace PlayerCore
{
	enum class VideoRenderType:int
	{
		Render_Invalid,
		Render_OpenGL
	};
	class VideoRenderFactory
	{
	public:
		static unique_ptr<VideoRender> create(VideoRenderType type, VideoFormat::PixelFormat format);
	};
}
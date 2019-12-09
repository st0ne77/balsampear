#pragma once
#include <memory>
#include "OpenGLRenderer.h"
#include <map>
#include "VideoFormat.h"
namespace balsampear
{
	enum class VideoRenderType:int
	{
		Render_Invalid,
		Render_OpenGL
	};
	class VideoRendererManager
	{
	public:
		virtual~ VideoRendererManager();
		static std::shared_ptr<OpenGLRenderer> getOpenGLRenderer(VideoFormat::PixelFormat fmt);

	private:
		VideoRendererManager();
		static VideoRendererManager *sing_;
		std::map<VideoFormat::PixelFormat, std::shared_ptr<OpenGLRenderer>> mapOpenGLRenderer_;
	};
}
#include "VideoRendererManager.h"
#include "OpenGLRenderFactory.h"

namespace balsampear
{
	VideoRendererManager* VideoRendererManager::sing_ = nullptr;

	VideoRendererManager::VideoRendererManager()
	{

	}

	std::shared_ptr<OpenGLRenderer> VideoRendererManager::getOpenGLRenderer(VideoFormat::PixelFormat fmt)
	{
		if (!sing_)
			sing_ = new VideoRendererManager;

		std::map<VideoFormat::PixelFormat, std::shared_ptr<OpenGLRenderer>>::iterator it = sing_->mapOpenGLRenderer_.find(fmt);
		if (it != sing_->mapOpenGLRenderer_.end())
		{
			return it->second;
		}


		std::shared_ptr<OpenGLRenderer> renderer = OpenGLRenderFactory::create(fmt);
		if (renderer)
		{
			sing_->mapOpenGLRenderer_[fmt] = renderer;
		}
		return renderer;
	}

	VideoRendererManager::~VideoRendererManager() = default;

	

}
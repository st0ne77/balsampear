#include <GLEW/GL/glew.h>
#include "PlayScreen.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include "AVPlayer.h"
#include "OpenGLShader.h"
#include "Base\StringPiece.h"
#include "VideoRendererManager.h"


using std::ifstream;
using std::stringstream;
using std::string;
using namespace balsampear;
namespace balsampear
{
	PlayScreen::PlayScreen()
		:PlayScreen(nullptr)
	{

	}

	PlayScreen::PlayScreen(QWidget* parent)
		: QOpenGLWidget(parent),
		curFormat_(VideoFormat::PixelFormat::Format_Invalid)
	{

	}

	PlayScreen::~PlayScreen()
	{
	}

	void PlayScreen::setFramePorter(std::weak_ptr<FramePorter> p)
	{
		porter_ = p.lock();
	}

	void PlayScreen::initializeGL()
	{
		GLenum err = glewInit();
	}

	void PlayScreen::resizeGL(int w, int h)
	{
		glViewport(0, 0, w, h);
	}

	void PlayScreen::paintGL()
	{
		std::shared_ptr<VideoFrame> frame;
		if (porter_ && (frame = porter_->frame()))
		{
			if (curFormat_ != frame->pixelFoemat())
			{
				curFormat_ = frame->pixelFoemat();
				renderer_ = VideoRendererManager::getOpenGLRenderer(curFormat_);
			}

			if (renderer_)
			{
				glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);
				renderer_->useShader();
				renderer_->fillData(frame->data(), frame->width(), frame->height());
				renderer_->useVertex();
				renderer_->Draw();
			}
		}
	}

}

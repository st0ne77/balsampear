#include <GLEW/GL/glew.h>
#include "OpenGLPlayWidget.h"
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
	OpenGLPlayWidget::OpenGLPlayWidget()
		:OpenGLPlayWidget(nullptr)
	{

	}

	OpenGLPlayWidget::OpenGLPlayWidget(QWidget* parent)
		: QOpenGLWidget(parent),
		curFormat_(VideoFormat::PixelFormat::Format_Invalid)
	{

	}

	OpenGLPlayWidget::~OpenGLPlayWidget()
	{
	}

	void OpenGLPlayWidget::setFramePorter(std::weak_ptr<FramePorter> p)
	{
		porter_ = p.lock();
	}

	void OpenGLPlayWidget::initializeGL()
	{
		GLenum err = glewInit();
	}

	void OpenGLPlayWidget::resizeGL(int w, int h)
	{
		glViewport(0, 0, w, h);
	}

	void OpenGLPlayWidget::paintGL()
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
		else
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}
	}

}

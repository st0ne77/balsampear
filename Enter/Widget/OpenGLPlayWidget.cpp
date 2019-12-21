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
	OpenGLPlayWidget::OpenGLPlayWidget(QWidget* parent)
		: QOpenGLWidget(parent),
		curFormat_(VideoFormat::PixelFormat::Format_Invalid)
	{

	}

	OpenGLPlayWidget::~OpenGLPlayWidget()
	{
	}


	void OpenGLPlayWidget::refresh(std::weak_ptr<VideoFrame> frame)
	{
		curFrame_ = frame.lock();
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
		if (curFrame_)
		{
			if (curFormat_ != curFrame_->pixelFoemat())
			{
				curFormat_ = curFrame_->pixelFoemat();
				renderer_ = VideoRendererManager::getOpenGLRenderer(curFormat_);
			}

			if (renderer_)
			{
				glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);
				renderer_->useShader();
				renderer_->fillData(curFrame_->data(), curFrame_->width(), curFrame_->height());
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

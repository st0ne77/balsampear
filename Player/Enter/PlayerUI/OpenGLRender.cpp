#include "OpenGLRender.h"
#include <iostream>
#include "QOpenGLFunctions_3_3_Core"
#include "QOpenGLContext"

namespace PlayerCore
{

	OpenGLRender::OpenGLRender()
		:VideoRender(),
		vertex_(0)
	{
	}

	OpenGLRender::~OpenGLRender() = default;

	void OpenGLRender::init()
	{
		initVertex();
		initTexture();
		initShader();
	}

	void OpenGLRender::render()
	{

	}

	void OpenGLRender::initVertex()
	{
	}

}
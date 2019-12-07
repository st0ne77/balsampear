#pragma once
#include "OpenGLRender.h"

namespace PlayerCore
{
	class OpenGLShader;
	class OpenGLYUV420PRender:public OpenGLRender
	{
	public:
		OpenGLYUV420PRender();
		virtual ~OpenGLYUV420PRender();

		virtual void initTexture();
		virtual void initShader();
		virtual void fillData();

	protected:
		OpenGLYUV420PRender(const OpenGLYUV420PRender&) = delete;
		OpenGLYUV420PRender& operator=(const OpenGLYUV420PRender&) = delete;

	protected:
		unsigned int texture_[3];
		OpenGLShader *shader_;
	};
}
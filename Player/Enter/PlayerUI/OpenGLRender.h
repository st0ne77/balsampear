#pragma once
#include <VideoRender.h>

namespace PlayerCore
{
	//non-thread-safe
	//use in ui thread
	class OpenGLRender : public VideoRender
	{
	public:
		OpenGLRender();
		virtual ~OpenGLRender();

		virtual void init();
		virtual void render();
		void initVertex();
		virtual void initTexture() = 0;
		virtual void initShader() = 0;
	protected:
		OpenGLRender(const OpenGLRender&) = delete;
		OpenGLRender& operator=(const OpenGLRender&) = delete;
		virtual void fillData() = 0;

	protected:
		unsigned int vertex_;
	};
}

#pragma once
#include "OpenGLRenderer.h"


namespace balsampear
{
	class OpenGLYUV420PRender:public OpenGLRenderer
	{
	public:
		OpenGLYUV420PRender();
		virtual ~OpenGLYUV420PRender();

		virtual void createTexture();
		virtual void fillData(const Byte* data, int width, int height);
	private:

	protected:
		unsigned int textureYUV[3];
		
	};
}
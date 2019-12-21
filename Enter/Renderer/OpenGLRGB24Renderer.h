#pragma once
#include "OpenGLRenderer.h"

namespace balsampear
{
	class OpenGLRGB24Renderer:public OpenGLRenderer
	{
	public:
		OpenGLRGB24Renderer();
		virtual ~OpenGLRGB24Renderer();

		virtual void createTexture();
		virtual void fillData(const Byte* data, int width, int height);
	private:

	protected:
		unsigned int textureRGB;

	};
}

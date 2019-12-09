#pragma once
#include <VideoRenderer.h>

namespace balsampear
{
	class OpenGLRenderer : public VideoRenderer
	{
	public:
		OpenGLRenderer();
		virtual ~OpenGLRenderer();
		void createVertex();
		void useVertex();
		virtual void createTexture() = 0;
		virtual void createSahder() = 0;
		virtual void useShader() = 0;
		virtual void fillData(const Byte* data, int width, int height) = 0;
		void Draw();
	private:

	protected:
		unsigned int vertex_;
	};
}

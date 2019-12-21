#pragma once
#include <VideoRenderer.h>
#include "Base/StringPiece.h"

namespace balsampear
{
	class OpenGLRenderer : public VideoRenderer
	{
	public:
		OpenGLRenderer(const StringPiece& vert, const StringPiece& frag);
		virtual ~OpenGLRenderer();
		void createVertex();
		void useVertex();
		virtual void createTexture() = 0;
		void createSahder();
		void useShader();
		virtual void fillData(const Byte* data, int width, int height) = 0;
		void Draw();
	private:

	protected:
		StringPiece vertFile_;
		StringPiece fragFile_;
		unsigned int vertex_;
		unsigned int shader_;
	};
}

#include "OpenGLRGB24Renderer.h"
#include "GL/glew.h"
namespace balsampear 
{
	OpenGLRGB24Renderer::OpenGLRGB24Renderer()
		:OpenGLRenderer("..\\shader\\rgb24.vert", "..\\shader\\rgb24.frag"),
		textureRGB(0)
	{

	}

	OpenGLRGB24Renderer::~OpenGLRGB24Renderer() = default;

	void OpenGLRGB24Renderer::createTexture()
	{
		glGenTextures(1, &textureRGB);
		glBindTexture(GL_TEXTURE_2D, textureRGB);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	void OpenGLRGB24Renderer::fillData(const Byte* data, int width, int height)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureRGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glUniform1i(glGetUniformLocation(shader_, "textureRGB"), 0);
	}

}


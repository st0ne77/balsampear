#include "OpenGLYUV420PRenderer.h"
#include "GL/glew.h"

using namespace std;
namespace balsampear
{

	OpenGLYUV420PRender::OpenGLYUV420PRender()
		:OpenGLRenderer("..\\shader\\yuv420p.vert", "..\\shader\\yuv420p.frag"),
		textureYUV {0,0,0}
	{

	}

	OpenGLYUV420PRender::~OpenGLYUV420PRender()
	{

	}

	void OpenGLYUV420PRender::createTexture()
	{
		glGenTextures(3, textureYUV);
		for (int i = 0; i < 3; ++i)
		{
			glBindTexture(GL_TEXTURE_2D, textureYUV[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}


	void OpenGLYUV420PRender::fillData(const Byte* data, int width, int height)
	{
		size_t sizeY = (size_t)width * height;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureYUV[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureYUV[1]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width / 2, height / 2, 0, GL_RED, GL_UNSIGNED_BYTE, data + sizeY);
		glGenerateMipmap(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textureYUV[2]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width / 2, height / 2, 0, GL_RED, GL_UNSIGNED_BYTE, data + sizeY * 5 / 4);
		glGenerateMipmap(GL_TEXTURE_2D);

		glUniform1i(glGetUniformLocation(shader_, "textureY"), 0);
		glUniform1i(glGetUniformLocation(shader_, "textureU"), 1);
		glUniform1i(glGetUniformLocation(shader_, "textureV"), 2);
	}

}
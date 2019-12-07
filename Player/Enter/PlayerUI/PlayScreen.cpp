#include "PlayScreen.h"
#include <iostream>

#include <fstream>
#include <sstream>
#include <iostream>
#include "AVPlayer.h"
#include "OpenGLShader.h"

using std::ifstream;
using std::stringstream;
using std::string;

PlayScreen::PlayScreen()
	:PlayScreen(nullptr)
{

}

PlayScreen::PlayScreen(QWidget* parent)
	: QOpenGLWidget(parent),
	core(nullptr)
{

}

PlayScreen::~PlayScreen()
{
}

unsigned int textureYUV[3];
unsigned int VAO;
PlayerCore::OpenGLShader* Shader = nullptr;
void PlayScreen::initializeGL()
{
	core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();

	float vertices[] = {
		// positions          // colors           // texture coords
		 1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // top right
		 1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // bottom right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // bottom left
		-1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	unsigned int VBO, EBO;
	core->glGenVertexArrays(1, &VAO);
	core->glGenBuffers(1, &VBO);
	core->glGenBuffers(1, &EBO);
	core->glBindVertexArray(VAO);
	core->glBindBuffer(GL_ARRAY_BUFFER, VBO);
	core->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	core->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	core->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	core->glEnableVertexAttribArray(0);
	// color attribute
	core->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	core->glEnableVertexAttribArray(1);
	// texture coord attribute
	core->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	core->glEnableVertexAttribArray(2);


	core->glGenTextures(3, textureYUV);
	for (int i = 0; i < 3; ++i)
	{
		core->glBindTexture(GL_TEXTURE_2D, textureYUV[i]);
		core->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		core->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		core->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		core->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	core->glBindBuffer(GL_ARRAY_BUFFER, 0);
	core->glBindVertexArray(0);

	Shader = new PlayerCore::OpenGLShader("..\\shader\\yuv420p.vert", "..\\shader\\yuv420p.frag");
}

void PlayScreen::resizeGL(int w, int h)
{
	core->glViewport(0, 0, w, h);
}

void PlayScreen::paintGL()
{
	if (render__&& render__->frame_ && Shader)
	{
		// render
		core->glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		core->glClear(GL_COLOR_BUFFER_BIT);
		
		Shader->use();
		size_t size = render__->frame_->width() * render__->frame_->height();

		core->glActiveTexture(GL_TEXTURE0);
		core->glBindTexture(GL_TEXTURE_2D, textureYUV[0]);
		core->glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, render__->frame_->width(), render__->frame_->height(), 0, GL_RED, GL_UNSIGNED_BYTE, &render__->frame_->data()[0]);
		core->glGenerateMipmap(GL_TEXTURE_2D);
		core->glActiveTexture(GL_TEXTURE1);
		core->glBindTexture(GL_TEXTURE_2D, textureYUV[1]);
		core->glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, render__->frame_->width() / 2, render__->frame_->height() / 2, 0, GL_RED, GL_UNSIGNED_BYTE, &render__->frame_->data()[size]);
		core->glGenerateMipmap(GL_TEXTURE_2D);
		core->glActiveTexture(GL_TEXTURE2);
		core->glBindTexture(GL_TEXTURE_2D, textureYUV[2]);
		core->glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, render__->frame_->width() / 2, render__->frame_->height() / 2, 0, GL_RED, GL_UNSIGNED_BYTE, &render__->frame_->data()[size * 5 / 4]);
		core->glGenerateMipmap(GL_TEXTURE_2D);

		Shader->setInt("textureY", 0);
		Shader->setInt("textureU", 1);
		Shader->setInt("textureV", 2);

		core->glBindVertexArray(VAO);
		core->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}



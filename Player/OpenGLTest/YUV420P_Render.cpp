#include "glad/glad.h"
#include <glfw3.h>
#include "YUV420P_Render.h"
#include <iostream>
#include "Shader.h"
#include "AVPlayer.h"


using namespace balsampear;
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(768, 432, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 768, 432);

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
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//RGBÎÆÀí
	unsigned int textureRGB;
	glGenTextures(1, &textureRGB);
	glBindTexture(GL_TEXTURE_2D, textureRGB);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned int textureYUV[3];
	glGenTextures(3, textureYUV);
	for (int i = 0; i < 3; ++i)
	{
		glBindTexture(GL_TEXTURE_2D, textureYUV[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	AVPlayer player;
	if (!player.load("E:\\Project\\TestFile\\110.mp4"))
	{
		return 0;
	}
	player.start();
	player.setProgressChangeCallBack([](double d) {
		//std::cout <<"timestamp:"<< d<<std::endl;
		if (0.68 - d<= 0.01)
		{
			int i = 0;
		}
		});



	Shader shader("..\\shader\\yuv420p.vert", "..\\shader\\yuv420p.frag");
	while (!glfwWindowShouldClose(window))
	{
		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		/*
		VideoFrame frame;
		player.videoFrames.tack(frame);
		shader.use();
		const Byte* data = frame.data();
		size_t ySize = (size_t)frame.width() * frame.height();
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureRGB);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.width(), frame.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, frame.getBuffer());
		glGenerateMipmap(GL_TEXTURE_2D);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureYUV[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, frame.width(), frame.height(), 0, GL_RED, GL_UNSIGNED_BYTE, &data[0]);
		glGenerateMipmap(GL_TEXTURE_2D);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textureYUV[1]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, frame.width() / 2, frame.height() / 2, 0, GL_RED, GL_UNSIGNED_BYTE, &data[ySize]);
		glGenerateMipmap(GL_TEXTURE_2D);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, textureYUV[2]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, frame.width() / 2, frame.height() / 2, 0, GL_RED, GL_UNSIGNED_BYTE, &data[ySize * 5 / 4]);
		glGenerateMipmap(GL_TEXTURE_2D);

		shader.setInt("textureRGB", 0);
		shader.setInt("textureY", 1);
		shader.setInt("textureU", 2);
		shader.setInt("textureV", 3);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/

		glfwSwapBuffers(window);
		glfwPollEvents();
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}
	glfwTerminate();
	return 0;
}
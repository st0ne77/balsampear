#include "OpenGLRenderer.h"
#include "GL/glew.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
namespace balsampear
{
	OpenGLRenderer::OpenGLRenderer(const StringPiece& vert, const StringPiece& frag)
		:VideoRenderer(),
		vertFile_(vert),
		fragFile_(frag),
		vertex_(0),
		shader_(0)
	{

	}

	OpenGLRenderer::~OpenGLRenderer()
	{

	}

	void OpenGLRenderer::createVertex()
	{
		float vertices[] = 
		{
			// positions          // colors           // texture coords
			 1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // top right
			 1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // bottom right
			-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // bottom left
			-1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f  // top left 
		};
		unsigned int indices[] = 
		{
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		unsigned int VBO, EBO;
		glGenVertexArrays(1, &vertex_);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(vertex_);
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

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void OpenGLRenderer::useVertex()
	{
		glBindVertexArray(vertex_);
	}

	void OpenGLRenderer::createSahder()
	{
		StringPiece vertexCode;
		StringPiece fragmentCode;
		ifstream vShaderFile;
		ifstream fShaderFile;
		// 保证ifstream对象可以抛出异常：
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			// 打开文件
			vShaderFile.open(vertFile_);
			fShaderFile.open(fragFile_);
			std::stringstream vertShaderStream, fragShaderStream;
			// 读取文件的缓冲内容到数据流中
			vertShaderStream << vShaderFile.rdbuf();
			fragShaderStream << fShaderFile.rdbuf();
			// 关闭文件处理器
			vShaderFile.close();
			fShaderFile.close();
			// 转换数据流到string
			vertexCode = vertShaderStream.str();
			fragmentCode = fragShaderStream.str();
		}
		catch (ifstream::failure e)
		{
			std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		//编译顶点着色器
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vShaderCode, NULL);
		glCompileShader(vertexShader);
		int success = 0;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//编译片段着色器
		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		shader_ = glCreateProgram();
		glAttachShader(shader_, vertexShader);
		glAttachShader(shader_, fragmentShader);
		glLinkProgram(shader_);
		// 打印连接错误（如果有的话）
		glGetProgramiv(shader_, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader_, 512, NULL, infoLog);
			std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		// 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void OpenGLRenderer::useShader()
	{
		glUseProgram(shader_);
	}

	void OpenGLRenderer::Draw()
	{
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

}
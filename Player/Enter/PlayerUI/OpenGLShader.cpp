#include "OpenGLShader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "QOpenGLFunctions_3_3_Core"
#include "QOpenGLContext"

using std::ifstream;
using std::stringstream;
namespace balsampear
{
	OpenGLShader::OpenGLShader(const StringPiece& vert, const StringPiece& frag)
		:id_(0)
	{
		QOpenGLFunctions_3_3_Core* core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
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
			vShaderFile.open(vert);
			fShaderFile.open(frag);
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
		int vertexShader = core->glCreateShader(GL_VERTEX_SHADER);
		core->glShaderSource(vertexShader, 1, &vShaderCode, NULL);
		core->glCompileShader(vertexShader);
		int success = 0;
		char infoLog[512];
		core->glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			core->glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//编译片段着色器
		int fragmentShader = core->glCreateShader(GL_FRAGMENT_SHADER);
		core->glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
		core->glCompileShader(fragmentShader);
		core->glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			core->glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		id_ = core->glCreateProgram();
		core->glAttachShader(id_, vertexShader);
		core->glAttachShader(id_, fragmentShader);
		core->glLinkProgram(id_);
		// 打印连接错误（如果有的话）
		core->glGetProgramiv(id_, GL_LINK_STATUS, &success);
		if (!success)
		{
			core->glGetProgramInfoLog(id_, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		// 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
		core->glDeleteShader(vertexShader);
		core->glDeleteShader(fragmentShader);
	}

	OpenGLShader::~OpenGLShader() = default;

	void OpenGLShader::use()
	{
		QOpenGLFunctions_3_3_Core* core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
		core->glUseProgram(id_);
	}

	void OpenGLShader::setFloat(const StringPiece & name, float value) const
	{
		QOpenGLFunctions_3_3_Core* core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
		core->glUniform1f(core->glGetUniformLocation(id_, name.c_str()), value);
	}

	void OpenGLShader::setInt(const StringPiece & name, int value) const
	{
		QOpenGLFunctions_3_3_Core* core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
		core->glUniform1i(core->glGetUniformLocation(id_, name.c_str()), value);
	}

}
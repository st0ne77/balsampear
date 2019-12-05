#include "GLTest.h"
#include <QDebug>
GLuint VBO, VAO;
const char* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"void main(){\n"
"  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n\0";
const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";
GLTest::GLTest(QWidget* parent) 
	:QOpenGLWidget(parent)
{

}

GLTest::~GLTest() {

}

void GLTest::initializeGL() {

	//着色器部分
	core = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();//获取上下文
	int vertexShader = core->glCreateShader(GL_VERTEX_SHADER);
	core->glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	core->glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	core->glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		core->glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}
	// fragment shader
	int fragmentShader = core->glCreateShader(GL_FRAGMENT_SHADER);

	core->glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	core->glCompileShader(fragmentShader);
	// check for shader compile errors
	core->glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		core->glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}
	shaderProgram = core->glCreateProgram();
	core->glAttachShader(shaderProgram, vertexShader);
	core->glAttachShader(shaderProgram, fragmentShader);
	core->glLinkProgram(shaderProgram);
	// check for linking errors
	core->glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		core->glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}
	core->glDeleteShader(vertexShader);
	core->glDeleteShader(fragmentShader);

	//VAO，VBO数据部分
	GLfloat vertices[] = {
			-0.5f, -0.5f, 0.0f, // left
			 0.5f, -0.5f, 0.0f, // right
			 0.0f,  0.5f, 0.0f  // top
	};


	core->glGenVertexArrays(1, &VAO);//两个参数，第一个为需要创建的缓存数量。第二个为用于存储单一ID或多个ID的GLuint变量或数组的地址
	core->glGenBuffers(1, &VBO);
	core->glBindVertexArray(VAO);
	core->glBindBuffer(GL_ARRAY_BUFFER, VBO);

	core->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	core->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	core->glEnableVertexAttribArray(0);

	core->glBindBuffer(GL_ARRAY_BUFFER, 0);
	core->glBindVertexArray(0);

}

void GLTest::resizeGL(int w, int h) {
	core->glViewport(0, 0, w, h);
}

void GLTest::paintGL() {
	core->glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	core->glClear(GL_COLOR_BUFFER_BIT);

	core->glUseProgram(shaderProgram);
	core->glBindVertexArray(VAO);
	core->glDrawArrays(GL_TRIANGLES, 0, 3);
	core->glUseProgram(0);

	QOpenGLWidget::makeCurrent()

}
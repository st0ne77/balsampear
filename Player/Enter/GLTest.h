#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
class GLTest:public QOpenGLWidget
{
public:
	explicit GLTest(QWidget* parent);
	~GLTest();
protected:
	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
	virtual void paintGL();
private:
	GLuint shaderProgram;
	QOpenGLFunctions_3_3_Core* core;
};


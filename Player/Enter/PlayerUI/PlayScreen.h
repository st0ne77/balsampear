#pragma once
#include <QOpenGLWidget>
#include "QOpenGLContext"
#include <QOpenGLFunctions_3_3_Core>
#include "VideoRender.h"
#include <memory>

class PlayScreen :public QOpenGLWidget
{
public:
	PlayScreen();
	explicit PlayScreen(QWidget* parent);
	virtual ~PlayScreen();

	std::shared_ptr<PlayerCore::VideoRender> render__;
protected:
	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
	virtual void paintGL();

private:
	QOpenGLFunctions_3_3_Core* core;
};




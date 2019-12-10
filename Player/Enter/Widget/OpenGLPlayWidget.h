#pragma once
#include <QOpenGLWidget>
#include "FramePorter.h"
#include <memory>
#include "OpenGLRenderer.h"

namespace balsampear
{
	class OpenGLPlayWidget :public QOpenGLWidget
	{
	public:
		explicit OpenGLPlayWidget(QWidget* parent = nullptr);
		virtual ~OpenGLPlayWidget();

		void setFramePorter(std::weak_ptr<FramePorter> p);
	protected:
		virtual void initializeGL();
		virtual void resizeGL(int w, int h);
		virtual void paintGL();

	private:
		std::shared_ptr<FramePorter> porter_;
		VideoFormat::PixelFormat curFormat_;
		std::shared_ptr<OpenGLRenderer> renderer_;
	};
}





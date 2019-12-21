#pragma once
#include <QOpenGLWidget>
#include <memory>
#include "OpenGLRenderer.h"
#include "VideoFrame.h"

namespace balsampear
{
	class OpenGLPlayWidget :public QOpenGLWidget
	{
	public:
		explicit OpenGLPlayWidget(QWidget* parent = nullptr);
		virtual ~OpenGLPlayWidget();

		void refresh(std::weak_ptr<VideoFrame> frame);
	protected:
		virtual void initializeGL();
		virtual void resizeGL(int w, int h);
		virtual void paintGL();

	private:
		VideoFormat::PixelFormat curFormat_;
		std::shared_ptr<OpenGLRenderer> renderer_;
		std::shared_ptr<VideoFrame> curFrame_;
	};
}





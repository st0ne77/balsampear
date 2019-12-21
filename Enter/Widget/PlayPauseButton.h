#pragma once
#include "QWidget"
namespace balsampear
{
	class ControlWidget;
	class PlayPauseButton:public QWidget
	{
	public:
		Q_OBJECT
	public:
		explicit PlayPauseButton(QWidget* parent = nullptr);
		~PlayPauseButton();

		void setPlayingStatus(bool val);
	protected:
		virtual void paintEvent(QPaintEvent* event);
		virtual void mousePressEvent(QMouseEvent* event);
		virtual void leaveEvent(QEvent* event);
		virtual void enterEvent(QEvent* event);
	private:
		QPainterPath calcRoundTriangle(int x, int y, int side);
		QPainterPath calcPauseArea(int x, int y, int side);
	private:
		ControlWidget *controlWidget_;
		QPainterPath playArea;
		bool enter;
		bool playing;
	};
}
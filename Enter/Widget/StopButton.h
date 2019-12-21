#pragma once
#include "QWidget"
namespace balsampear
{
	class ControlWidget;
	class StopButton: public QWidget
	{
		Q_OBJECT
	public:
		explicit StopButton(QWidget *parant = nullptr);
		virtual ~StopButton();

	protected:
		virtual void paintEvent(QPaintEvent* event);
		virtual void enterEvent(QEvent* event);
		virtual void leaveEvent(QEvent* event);
		virtual void mousePressEvent(QMouseEvent* event);

	private:
		ControlWidget* controlWidget_;
		bool mouseEnter_;
	};
}
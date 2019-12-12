#include "StopButton.h"
#include "QPainter"
#include "ControlWidget.h"
namespace balsampear
{
	StopButton::StopButton(QWidget* parant)
		:QWidget(parant),
		mouseEnter_(false)
	{
		controlWidget_ = dynamic_cast<ControlWidget*>(parant);
	}

	StopButton::~StopButton() = default;

	void StopButton::paintEvent(QPaintEvent* event)
	{
		QPainter painter(this);
		int width = this->width() * 0.8;
		int height = this->height() * 0.8;

		QBrush brush = mouseEnter_ ? QColor(0xff, 0x66, 0x00) : QColor(0x99, 0x99, 0x99);
		painter.fillRect(0, 0, width, height, brush);
	}

	void StopButton::enterEvent(QEvent* event)
	{
		mouseEnter_ = true;
		update();
	}

	void StopButton::leaveEvent(QEvent* event)
	{
		mouseEnter_ = false;
		update();
	}

	void StopButton::mousePressEvent(QMouseEvent* event)
	{
		if (controlWidget_)
		{
			emit controlWidget_->stopPlay();
		}
	}

}
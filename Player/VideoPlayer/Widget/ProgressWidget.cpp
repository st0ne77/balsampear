#include "stdafx.h"
#include "ProgressWidget.h"

ProgressWidget::ProgressWidget(QWidget *parent) : QWidget(parent), Progress_(0.0)
{
}

ProgressWidget::~ProgressWidget()
{

}

void ProgressWidget::changeProgress(double progress)
{
	Progress_ = progress;
	update();
}

void ProgressWidget::paintEvent(QPaintEvent* event)
{
	int width = this->width();
	int height = this->height();

	QPainterPath painterDone;
	painterDone.addRect(2, (height / 2 - 2), ((double)width - 20) * Progress_, 4);

	QPainterPath painterWill;
	int x = (width - 20) * Progress_ + 2;
	int WillWidth = ((double)width - 20) * (1.0 - Progress_);

 	QPainter painter(this);

	painter.fillRect(2, (height / 2 - 2), ((double)width - 20) * Progress_, 4, QColor(10, 200, 0,255));
	painter.fillRect(x, (height / 2 - 2), WillWidth, 4, QColor(255, 255, 255, 80));

}

void ProgressWidget::mousePressEvent(QMouseEvent* event)
{
	int width = this->width();
	int height = this->height();
	int x = event->x();
	int y = event->y();

	if ( x >= 2 && x <= (width - 20)
		&& y >= (height / 2 - 2) && y < (height / 2 + 2))
	{
		//assert(0);
	}
}

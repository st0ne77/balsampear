#include "stdafx.h"
#include "ControlWidget.h"



ControlWidget::ControlWidget(QWidget* parent)
	:QWidget(parent),
	progress_(this),
	playBtn(this)
{
	setMinimumSize(400, 100);
}



void ControlWidget::paintEvent(QPaintEvent* event)
{
	int width = this->width();
	int height = this->height();

	QPainter painter(this);
	painter.setBrush(Qt::black);
	painter.drawRect(0, 0, this->width(), this->height()); //ÏÈ»­³ÉºÚÉ«

	progress_.move(width * 0.02, height * 0.2);
	progress_.resize(width, 10);

	playBtn.move(width*0.02, height*0.6);
	playBtn.resize(width*0.05, height*0.3);
}






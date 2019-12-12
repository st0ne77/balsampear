#include "ProgressWidget.h"
#include "QPainter"
namespace balsampear
{
	ProgressWidget::ProgressWidget(QWidget* parent)
		:QWidget(parent),
		progress_(0.0)
	{

	}

	ProgressWidget::~ProgressWidget()
	{

	}

	void ProgressWidget::setPlayProgress(double progress)
	{
		progress_ = progress;
		update();
	}

	void ProgressWidget::paintEvent(QPaintEvent* event)
	{
		int width = this->width();
		int height = this->height();

		int x = width * progress_;
		int will = width - width* progress_;

		QPainter painter(this);

		painter.fillRect(0, 0, x, height, QColor(10, 200, 0, 255));
		painter.fillRect(x, 0, will, height, QColor(255, 255, 255, 80));
	}

	void ProgressWidget::mousePressEvent(QMouseEvent* event)
	{

	}

}



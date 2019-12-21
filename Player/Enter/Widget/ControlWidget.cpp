#include "ControlWidget.h"
#include "QPainter"
namespace balsampear
{
	ControlWidget::ControlWidget(QWidget* parant)
		:progress_(this),
		playButton_(this),
		stopButton_(this)
	{

	}

	ControlWidget::~ControlWidget() = default;

	void ControlWidget::setPlayingStatus(bool _val)
	{
		playButton_.setPlayingStatus(_val);
	}

	void ControlWidget::setPlayProgress(double d)
	{
		progress_.setPlayProgress(d);
	}

	void ControlWidget::paintEvent(QPaintEvent* event)
	{
		int width = this->width();
		int height = this->height();

		QPainter painter(this);
		painter.setBrush(Qt::black);
		painter.drawRect(0, 0, width, height); //ÏÈ»­³ÉºÚÉ«

		playButton_.move(width * 0.5 - height * 0.5, height * 0.3);
		playButton_.resize(height * 0.6, height * 0.6);

		stopButton_.resize(height * 0.6, height * 0.6);
		stopButton_.move(width - height, height * 0.3);

		progress_.resize(width, 4);
		progress_.move(0, 0);
	}

}



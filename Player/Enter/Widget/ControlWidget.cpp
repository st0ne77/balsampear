#include "ControlWidget.h"
namespace balsampear
{
	ControlWidget::ControlWidget(QWidget* parant)
		:playButton_(this),
		stopButton_(this)
	{

	}

	ControlWidget::~ControlWidget() = default;

	void ControlWidget::setPlayingStatus(bool _val)
	{
		playButton_.setPlayingStatus(_val);
	}

	void ControlWidget::paintEvent(QPaintEvent* event)
	{
		int width = this->width();
		int height = this->height();

		playButton_.move(width * 0.5 - height * 0.5, 0);
		playButton_.resize(height, height);

		stopButton_.resize(height * 0.7, height * 0.7);
		stopButton_.move(width - height, 0);
	}

}



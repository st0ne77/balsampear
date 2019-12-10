#include "PlayPauseButton.h"
#include "QPainter"
#include "ControlWidget.h"
namespace balsampear
{
	PlayPauseButton::PlayPauseButton(QWidget* parent)
		:QWidget(parent),
		enter(false),
		playing(false)
	{
		controlWidget_ = dynamic_cast<ControlWidget*>(parent);
	}

	PlayPauseButton::~PlayPauseButton() = default;

	void PlayPauseButton::setPlayingStatus(bool val)
	{
		playing = val; 
		update();
	}

	void PlayPauseButton::paintEvent(QPaintEvent* event)
	{
		QPainter painter(this);
		int height = this->height();
		playArea = playing ? calcPauseArea(0, 0, 0.8 * height) : calcRoundTriangle(0, 0, 0.8 * height);
		QPainterPath path = playArea;
		painter.setRenderHint(QPainter::Antialiasing, true);

		QBrush brush = enter ? QColor(0xff, 0x66, 0x00) : QColor(0x99, 0x99, 0x99);
		painter.fillPath(path, brush);
	}

	void PlayPauseButton::mousePressEvent(QMouseEvent* event)
	{
		if (controlWidget_)
		{
			emit controlWidget_->checkChangePlayStatus();
		}
		update();
	}

	void PlayPauseButton::leaveEvent(QEvent* event)
	{
		enter = false;
		update();
	}

	void PlayPauseButton::enterEvent(QEvent* event)
	{
		enter = true;
		update();
	}

	QPainterPath PlayPauseButton::calcRoundTriangle(int x, int y, int side)
	{
		x = x + side * 0.15;
		QPainterPath result;
		QPolygon triangle;
		double sin60_ = sin(60 * 3.1415926 / 180);
		double sin30_ = sin(30 * 3.1415926 / 180);
		triangle << QPoint{ x, y };
		triangle << QPoint{ x + (int)(sin60_ * side), y + side / 2 };
		triangle << QPoint{ x, y + side };
		triangle << QPoint{ x, y };
		result.addPolygon(triangle);

		QPainterPath round;
		int radius = (int)(side / (2 * sin60_));
		int centerX = x + (int)(sin30_ * radius);
		int centerY = y + side / 2;
		round.addEllipse(centerX - radius + 2, centerY - radius + 2, radius * 2 - 4, radius * 2 - 4);
		QPainterPath tmp = result.subtracted(round);
		result = result.subtracted(tmp);
		return result;
	}

	QPainterPath PlayPauseButton::calcPauseArea(int x, int y, int side)
	{
		QPainterPath result;
		result.addRect(x + side * 0.15, y + side * 0.1, side * 0.2, side * 0.8);
		result.addRect(x + side * 0.55, y + side * 0.1, side * 0.2, side * 0.8);
		return result;
	}

}
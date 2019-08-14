#include "stdafx.h"
#include "ControlButton.h"


ControlButton::ControlButton(QWidget *parent)
	:QPushButton(parent)
{
	mbPlaying = false;
	setStyleSheet("QPushButton{image: url(:/start_normal.png);\nborder-radius:2px;\nheight:35px}");
}

ControlButton::~ControlButton()
{

}

void ControlButton::setPlaying(bool _val)
{
	mbPlaying = _val;
}

void ControlButton::enterEvent(QEvent* event)
{
	if (mbPlaying)
	{
		setStyleSheet("QPushButton{image: url(:/pause_focus.png);\nborder-radius:2px;\nheight:35px}");
	}
	else
	{
		setStyleSheet("QPushButton{image: url(:/start_focus.png);\nborder-radius:2px;\nheight:35px}");
	}
}

void ControlButton::leaveEvent(QEvent* event)
{
	if (mbPlaying)
	{
		setStyleSheet("QPushButton{image: url(:/pause_normal.png);\nborder-radius:2px;\nheight:35px}");
	}
	else
	{
		setStyleSheet("QPushButton{image: url(:/start_normal.png);\nborder-radius:2px;\nheight:35px}");
	}
}


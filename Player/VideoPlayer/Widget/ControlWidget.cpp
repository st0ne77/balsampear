#include "stdafx.h"
#include "ControlWidget.h"
#include "ControlButton.h"
#include <QHBoxLayout>
#include "PlayWidget.h"
#include "AudioDecoder.h"
#include "VideoDecoder.h"
#include "ProgressWidget.h"

ControlWidget::ControlWidget(QWidget* parent)
	:QWidget(parent),
	player(dynamic_cast<PlayWidget*>(parent)),
	mbPlying(false),
	mHBoxLayout(new QHBoxLayout(this)),
	mpControlButton(new ControlButton(this)),
	totaltime_(271)
{
	pProgressWidget_ = new ProgressWidget(this);
	mHBoxLayout->addWidget(pProgressWidget_, 9);
    mHBoxLayout->addWidget(mpControlButton, 2);
    mHBoxLayout->addWidget(new QWidget(), 9);

	connect(mpControlButton, SIGNAL(clicked()), this, SLOT(changePlayStatus()));

	player.play("E:\\Project\\TestFile\\video.mp4");
}

void ControlWidget::changePlayStatus()
{
	if (mbPlying)
	{
		player.pause();
		mbPlying = false;
	}
	else
	{
		player.start();
		mbPlying = true;
	}
}


void ControlWidget::ProgressChanged(int progress)
{
	pProgressWidget_->ProgressChanged((double)progress / totaltime_);
}

void ControlWidget::paintEvent(QPaintEvent* event)
{
	pProgressWidget_->resize(this->width(), 50);
}


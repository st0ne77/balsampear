#include "stdafx.h"
#include "ControlWidget.h"
#include "ControlButton.h"
#include <QHBoxLayout>
#include "PlayWidget.h"
#include "AudioDecoder.h"
#include "VideoDecoder.h"
#include "ProgressWidget.h"

ControlWidget::ControlWidget(QWidget* parent, OutDevice* output)
	:QWidget(parent),
	player(output),
	started_(false),
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
	connect(&player, SIGNAL(ProgressChanged(double)), pProgressWidget_, SLOT(ProgressChanged(double)));
	connect(&player, SIGNAL(end()), this, SLOT(end()));
}

void ControlWidget::play(const QString& video)
{
	player.play(video.toStdString());
	started_ = true;
}

void ControlWidget::stop()
{
	player.stop();
	started_ = false;
	mbPlying = false;
	mpControlButton->setPlaying(mbPlying);
}

void ControlWidget::changePlayStatus()
{
	if (started_)
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
		mpControlButton->setPlaying(mbPlying);
	}
}



void ControlWidget::end()
{
	stop();
}

void ControlWidget::paintEvent(QPaintEvent* event)
{
	pProgressWidget_->resize(this->width(), 50);

	QPainter painter(this);
	painter.setBrush(Qt::black);
	painter.drawRect(0, 0, this->width(), this->height()); //ÏÈ»­³ÉºÚÉ«
}


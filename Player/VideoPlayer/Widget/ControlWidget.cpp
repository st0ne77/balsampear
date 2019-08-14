#include "stdafx.h"
#include "ControlWidget.h"
#include "ControlButton.h"
#include <QHBoxLayout>
#include "PlayWidget.h"
#include "PlayerTimer.h"

ControlWidget::ControlWidget(QWidget* parent, PlayerTimer* playTimer) :
	QWidget(parent),
	mpPlayTimer(playTimer),
	mbPlying(false),
	mHBoxLayout(new QHBoxLayout(this)),
	mpControlButton(new ControlButton(this))

{
	mHBoxLayout->addWidget(new QWidget(), 9);
    mHBoxLayout->addWidget(mpControlButton, 2);
    mHBoxLayout->addWidget(new QWidget(), 9);

	connect(mpControlButton, SIGNAL(clicked()), this, SLOT(changePlayStatus()));
}

void ControlWidget::changePlayStatus()
{
	if (mbPlying)
	{
		mpPlayTimer->PausePlay();
		mpControlButton->setPlaying(false);
	}
	else
	{
		mpPlayTimer->StartPlay(30);
		mbPlying = true;
		mpControlButton->setPlaying(true);
	}
}


